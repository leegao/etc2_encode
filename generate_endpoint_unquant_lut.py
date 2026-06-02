def generate_packed_astc_unquant_tables():
    ENDPOINT_MAX_VALUES = [
        1,
        2,
        3,
        4,
        5,
        7,
        9,
        11,
        15,
        19,
        23,
        31,
        39,
        47,
        63,
        79,
        95,
        127,
        159,
        191,
        255,
    ]
    BITS_TRITS_QUINTS_TABLE = [
        (1, 0, 0),
        (0, 1, 0),
        (2, 0, 0),
        (0, 0, 1),
        (1, 1, 0),
        (3, 0, 0),
        (1, 0, 1),
        (2, 1, 0),
        (4, 0, 0),
        (2, 0, 1),
        (3, 1, 0),
        (5, 0, 0),
        (3, 0, 1),
        (4, 1, 0),
        (6, 0, 0),
        (4, 0, 1),
        (5, 1, 0),
        (7, 0, 0),
        (5, 0, 1),
        (6, 1, 0),
        (8, 0, 0),
    ]
    mixed_mode_params = {
        4: 204,
        6: 113,
        7: 93,
        9: 54,
        10: 44,
        12: 26,
        13: 22,
        15: 13,
        16: 11,
        18: 6,
        19: 5,
    }

    def compute_element(mode, val):
        tq = BITS_TRITS_QUINTS_TABLE[mode]
        if not tq[1] and not tq[2]:
            num_bits = tq[0]
            output, bits_to_fill = 0, 8
            while bits_to_fill > 0:
                chunk = min(bits_to_fill, num_bits)
                output = (output << chunk) | (val >> (num_bits - chunk))
                bits_to_fill -= chunk
            return output

        if mode == 1:
            return [0, 130, 255][val]
        if mode == 3:
            return [0, 65, 130, 190, 255][val]

        C = mixed_mode_params[mode]
        num_bits = tq[0]
        D, bits = val >> num_bits, val & ((1 << num_bits) - 1)

        a = (bits >> 0) & 1
        b = (bits >> 1) & 1 if num_bits > 1 else 0
        c = (bits >> 2) & 1 if num_bits > 2 else 0
        d = (bits >> 3) & 1 if num_bits > 3 else 0
        e = (bits >> 4) & 1 if num_bits > 4 else 0
        f = (bits >> 5) & 1 if num_bits > 5 else 0

        A = 511 if a else 0
        B = 0
        if mode == 7:
            B = (b << 8) | (b << 4) | (b << 2) | (b << 1)
        elif mode == 9:
            B = (b << 8) | (b << 3) | (b << 2)
        elif mode == 10:
            B = (c << 8) | (b << 7) | (c << 3) | (b << 2) | (c << 1) | b
        elif mode == 12:
            B = (c << 8) | (b << 7) | (c << 2) | (b << 1) | c
        elif mode == 13:
            B = (d << 8) | (c << 7) | (b << 6) | (d << 2) | (c << 1) | b
        elif mode == 15:
            B = (d << 8) | (c << 7) | (b << 6) | (d << 1) | c
        elif mode == 16:
            B = (e << 8) | (d << 7) | (c << 6) | (b << 5) | (e << 1) | d
        elif mode == 18:
            B = (e << 8) | (d << 7) | (c << 6) | (b << 5) | e
        elif mode == 19:
            B = (f << 8) | (e << 7) | (d << 6) | (c << 5) | (b << 4) | f

        T = (D * C + B) ^ A
        return (A & 0x80) | (T >> 2)

    packed_lut, offsets, current_offset = [], [], 0
    for mode in range(21):
        offsets.append(current_offset)
        ep_max = ENDPOINT_MAX_VALUES[mode]
        for v in range(ep_max + 1):
            packed_lut.append(compute_element(mode, v))
        current_offset += ep_max + 1

    print(
        f"static const int unquant_offsets[21] = {{ {', '.join(map(str, offsets))} }};\n"
    )
    print(f"static const uint unquant_lut[{len(packed_lut)}] = {{")
    for i in range(0, len(packed_lut), 16):
        print("    " + ", ".join(f"{x:3d}" for x in packed_lut[i : i + 16]) + ",")
    print("};")


generate_packed_astc_unquant_tables()
