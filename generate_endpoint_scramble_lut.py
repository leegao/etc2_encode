def generate_packed_astc_endpoint_lut():
    modes_config = {
        4: ("t", 1, 204, "000000000"),
        6: ("q", 1, 113, "000000000"),
        7: ("t", 2, 93, "b000b0bb0"),
        9: ("q", 2, 54, "b0000bb00"),
        10: ("t", 3, 44, "cb000cbcb"),
        12: ("q", 3, 26, "cb0000cbc"),
        13: ("t", 4, 22, "dcb000dcb"),
        15: ("q", 4, 13, "dcb0000dc"),
        16: ("t", 5, 11, "edcb000ed"),
        18: ("q", 5, 6, "edcb0000e"),
        19: ("t", 6, 5, "fedcb000f"),
    }

    packed_lut = []
    indices = []

    # Only process the non-pure modes, since pure modes
    # are not scrambled and can be handled directly
    for mode in [13, 19]:
        m_type, num_bits, C, B_pattern = modes_config[mode]
        max_D = 3 if m_type == "t" else 5
        max_m = 1 << num_bits
        pairs = []

        for D in range(max_D):
            for m in range(max_m):
                bits_dict = {"0": 0}
                for b_idx in range(num_bits):
                    char_name = chr(ord("a") + b_idx)
                    bits_dict[char_name] = (m >> b_idx) & 1

                B = 0
                for idx, char in enumerate(B_pattern):
                    bit_pos = 8 - idx
                    if char in bits_dict:
                        B |= bits_dict[char] << bit_pos

                a = bits_dict["a"]
                A = 0x1FF if a else 0

                T = D * C + B
                T = T ^ A
                T = (A & 0x80) | (T >> 2)

                packed_symbol = (D << num_bits) | m
                pairs.append((T, packed_symbol))

        pairs.sort(key=lambda x: x[0])
        indices.append(len(packed_lut))
        packed_lut.extend([p[1] for p in pairs])

    return packed_lut, indices


if __name__ == "__main__":
    packed_data, indices = generate_packed_astc_endpoint_lut()
    print(indices)
    print("size = ", len(packed_data))
    for i in range(0, len(packed_data), 16):
        chunk = packed_data[i : i + 16]
        print("    " + ", ".join(str(x) for x in chunk) + ",")
