import struct
import sys

import numpy as np
from PIL import Image

etc1_color_modifier_table = np.array(
    [[2, 8], [5, 17], [9, 29], [13, 42], [18, 60], [24, 80], [33, 106], [47, 183]],
    dtype=np.int32,
)

etc2_alpha_modifier_table = np.array(
    [
        [2, 5, 8, 14],
        [2, 6, 9, 12],
        [1, 4, 7, 12],
        [1, 3, 5, 12],
        [2, 5, 7, 11],
        [2, 6, 8, 10],
        [3, 6, 7, 10],
        [2, 4, 7, 10],
        [1, 5, 7, 9],
        [1, 4, 7, 9],
        [1, 3, 7, 9],
        [1, 4, 6, 9],
        [2, 3, 6, 9],
        [0, 1, 2, 9],
        [3, 5, 7, 8],
        [2, 4, 6, 8],
    ],
    dtype=np.int32,
)

etc2_distance_table = np.array([3, 6, 11, 16, 23, 32, 41, 64], dtype=np.int32)


def bitfieldExtract_unsigned(value, offset, bits):
    return (value >> offset) & ((1 << bits) - 1)


def bitfieldExtract_signed(value, offset, bits):
    mask = (1 << bits) - 1
    val = (value >> offset) & mask
    if val & (1 << (bits - 1)):
        val -= 1 << bits
    return val


def decode_etc2_block2(block_data_raw):
    # From https://github.com/Themaister/Granite/blob/4ad937d17fc5849996bbc3997aa5adf180c00630/assets/shaders/decode/etc2.comp
    if len(block_data_raw) != 16:
        raise ValueError("Must be exactly 16 bytes.")

    alpha_payload_y = struct.unpack(">I", block_data_raw[0:4])[0]
    alpha_payload_x = struct.unpack(">I", block_data_raw[4:8])[0]
    color_payload_y = struct.unpack(">I", block_data_raw[8:12])[0]
    color_payload_x = struct.unpack(">I", block_data_raw[12:16])[0]

    pixel_y, pixel_x = np.ogrid[0:4, 0:4]
    linear_pixel = 4 * pixel_x + pixel_y  # Shape: (4, 4)

    bit_offset = 45 - 3 * linear_pixel
    base_alpha = bitfieldExtract_unsigned(alpha_payload_y, 24, 8)
    multiplier = bitfieldExtract_unsigned(alpha_payload_y, 20, 4)
    table = bitfieldExtract_unsigned(alpha_payload_y, 16, 4)

    payload_arr = np.array([alpha_payload_x, alpha_payload_y], dtype=np.uint32)
    idx = bit_offset >> 5
    bit_rem = bit_offset & 31
    lsb_index = (payload_arr[idx] >> bit_rem) & 3

    bit_offset_msb = bit_offset + 2
    idx_msb = bit_offset_msb >> 5
    bit_rem_msb = bit_offset_msb & 31
    msb_alpha = (payload_arr[idx_msb] >> bit_rem_msb) & 1

    mod_alpha = etc2_alpha_modifier_table[table, lsb_index] ^ (
        msb_alpha.astype(np.int32) - 1
    )
    alpha_result = np.clip(base_alpha + mod_alpha * multiplier, 0, 255)

    flip = color_payload_y & 1
    coord_val = np.where(flip == 0, pixel_x, pixel_y)
    subblock = (coord_val & 2) >> 1  # Shape: (4, 4)

    etc1_compat = False
    rgb_result = np.zeros((4, 4, 3), dtype=np.int32)

    if (color_payload_y & 2) == 0:
        # Individual mode (ETC1)
        etc1_compat = True
        shift_r = 28 - 4 * subblock
        shift_g = 20 - 4 * subblock
        shift_b = 12 - 4 * subblock

        base_rgb = np.stack(
            [
                ((color_payload_y >> shift_r) & 0xF) * 0x11,
                ((color_payload_y >> shift_g) & 0xF) * 0x11,
                ((color_payload_y >> shift_b) & 0xF) * 0x11,
            ],
            axis=-1,
        )
    else:
        r = bitfieldExtract_unsigned(color_payload_y, 27, 5)
        rd = bitfieldExtract_signed(color_payload_y, 24, 3)
        g = bitfieldExtract_unsigned(color_payload_y, 19, 5)
        gd = bitfieldExtract_signed(color_payload_y, 16, 3)
        b = bitfieldExtract_unsigned(color_payload_y, 11, 5)
        bd = bitfieldExtract_signed(color_payload_y, 8, 3)

        r1 = r + rd
        g1 = g + gd
        b1 = b + bd

        if r1 < 0 or r1 > 31:
            # print("T mode")
            # T-Mode
            r1_t = bitfieldExtract_unsigned(color_payload_y, 56 - 32, 2) | (
                bitfieldExtract_unsigned(color_payload_y, 59 - 32, 2) << 2
            )
            g1_t = bitfieldExtract_unsigned(color_payload_y, 52 - 32, 4)
            b1_t = bitfieldExtract_unsigned(color_payload_y, 48 - 32, 4)
            r2_t = bitfieldExtract_unsigned(color_payload_y, 44 - 32, 4)
            g2_t = bitfieldExtract_unsigned(color_payload_y, 40 - 32, 4)
            b2_t = bitfieldExtract_unsigned(color_payload_y, 36 - 32, 4)

            da = (bitfieldExtract_unsigned(color_payload_y, 34 - 32, 2) << 1) | (
                color_payload_y & 1
            )
            dist = etc2_distance_table[da]

            msb = (color_payload_x >> (15 + linear_pixel)) & 2
            lsb = (color_payload_x >> linear_pixel) & 1
            index = msb | lsb

            c1 = np.array([r1_t, g1_t, b1_t], dtype=np.int32) * 0x11
            c2 = np.array([r2_t, g2_t, b2_t], dtype=np.int32) * 0x11
            mod = (2 - index)[..., None]
            # print(c1, c2, mod, dist)

            rgb_result = np.where(
                (index == 0)[..., None], c1, np.clip(c2 + mod * dist, 0, 255)
            )

        elif g1 < 0 or g1 > 31:
            # H-Mode
            r1_h = bitfieldExtract_unsigned(color_payload_y, 59 - 32, 4)
            g1_h = (bitfieldExtract_unsigned(color_payload_y, 56 - 32, 3) << 1) | (
                (color_payload_y >> 20) & 1
            )
            b1_h = bitfieldExtract_unsigned(color_payload_y, 47 - 32, 3) | (
                (color_payload_y >> 16) & 8
            )
            r2_h = bitfieldExtract_unsigned(color_payload_y, 43 - 32, 4)
            g2_h = bitfieldExtract_unsigned(color_payload_y, 39 - 32, 4)
            b2_h = bitfieldExtract_unsigned(color_payload_y, 35 - 32, 4)

            da = color_payload_y & 4
            db = color_payload_y & 1
            d = da + 2 * db

            if (r1_h * 0x10000 + g1_h * 0x100 + b1_h) >= (
                r2_h * 0x10000 + g2_h * 0x100 + b2_h
            ):
                d += 1

            dist = etc2_distance_table[d]
            msb = (color_payload_x >> (15 + linear_pixel)) & 2
            lsb = (color_payload_x >> linear_pixel) & 1

            c1 = np.array([r1_h, g1_h, b1_h], dtype=np.int32) * 0x11
            c2 = np.array([r2_h, g2_h, b2_h], dtype=np.int32) * 0x11

            base_color = np.where((msb != 0)[..., None], c2, c1)
            mod = (1 - 2 * lsb)[..., None]
            rgb_result = np.clip(base_color + mod * dist, 0, 255)

        elif b1 < 0 or b1 > 31:
            # Planar Mode
            r_p = bitfieldExtract_unsigned(color_payload_y, 57 - 32, 6)
            g_p = bitfieldExtract_unsigned(color_payload_y, 49 - 32, 6) | (
                (color_payload_y >> 18) & 0x40
            )
            b_p = (
                bitfieldExtract_unsigned(color_payload_y, 39 - 32, 3)
                | (bitfieldExtract_unsigned(color_payload_y, 43 - 32, 2) << 3)
                | ((color_payload_y >> 11) & 0x20)
            )

            rh = (color_payload_y & 1) | (
                bitfieldExtract_unsigned(color_payload_y, 2, 5) << 1
            )
            rv = bitfieldExtract_unsigned(color_payload_x, 13, 6)
            gh = bitfieldExtract_unsigned(color_payload_x, 25, 7)
            gv = bitfieldExtract_unsigned(color_payload_x, 6, 7)
            bh = bitfieldExtract_unsigned(color_payload_x, 19, 6)
            bv = bitfieldExtract_unsigned(color_payload_x, 0, 6)

            r_p = ((r_p << 2) | (r_p >> 4)) & 0xFF
            rh = ((rh << 2) | (rh >> 4)) & 0xFF
            rv = ((rv << 2) | (rv >> 4)) & 0xFF
            g_p = ((g_p << 1) | (g_p >> 6)) & 0xFF
            gh = ((gh << 1) | (gh >> 6)) & 0xFF
            gv = ((gv << 1) | (gv >> 6)) & 0xFF
            b_p = ((b_p << 2) | (b_p >> 4)) & 0xFF
            bh = ((bh << 2) | (bh >> 4)) & 0xFF
            bv = ((bv << 2) | (bv >> 4)) & 0xFF

            rgb = np.array([r_p, g_p, b_p], dtype=np.int32)
            dx = np.array([rh, gh, bh], dtype=np.int32) - rgb
            dy = np.array([rv, gv, bv], dtype=np.int32) - rgb

            dx_scaled = dx * pixel_x[..., None]
            dy_scaled = dy * pixel_y[..., None]

            rgb_result = rgb + ((dx_scaled + dy_scaled + 2) >> 2)
            rgb_result = np.clip(rgb_result, 0, 255)
        else:
            # Differential mode (ETC1)
            etc1_compat = True
            c0 = np.array([r, g, b], dtype=np.int32)
            c1 = np.array([r1, g1, b1], dtype=np.int32)
            base_rgb = np.where((subblock == 0)[..., None], c0, c1)
            base_rgb = (base_rgb << 3) | (base_rgb >> 2)

    if etc1_compat:
        etc1_table_index = (color_payload_y >> (5 - 3 * subblock)) & 7
        msb = (color_payload_x >> (15 + linear_pixel)) & 2
        lsb = (color_payload_x >> linear_pixel) & 1
        sgn = 1 - msb

        offset = etc1_color_modifier_table[etc1_table_index, lsb] * sgn
        rgb_result = np.clip(base_rgb + offset[..., None], 0, 255)

    rgba_output = np.zeros((4, 4, 4), dtype=np.uint8)
    rgba_output[..., :3] = rgb_result
    rgba_output[..., 3] = alpha_result

    return rgba_output


def main():
    if len(sys.argv) < 4:
        print("Usage: python decode.py <input.etc2> <width> <height>")
        return

    infile, w, h = (
        sys.argv[1],
        int(sys.argv[2]),
        int(sys.argv[3]),
    )
    with open(infile, "rb") as f:
        data = f.read()
    # reconstructed = np.array(Image.open("reconstructed.png").convert("RGBA"))

    canvas = np.zeros((h, w, 4), dtype=np.uint8)
    offset = 0
    for by in range(h // 4):
        for bx in range(w // 4):
            tile = decode_etc2_block2(data[offset : offset + 16])
            offset += 16
            # print(bx, by)
            # print(tile)
            # print()
            # print(reconstructed[by * 4 : (by + 1) * 4, bx * 4 : (bx + 1) * 4])
            canvas[by * 4 : (by + 1) * 4, bx * 4 : (bx + 1) * 4] = tile.transpose(
                1, 0, 2
            )
            # return

    Image.fromarray(canvas, "RGBA").save("decoded.png")
    print("Saved decoded.png")


if __name__ == "__main__":
    main()
