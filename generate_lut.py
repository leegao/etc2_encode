import numpy as np


def hash52(p: int) -> int:
    p &= 0xFFFFFFFF
    p ^= p >> 15
    p = (p - (p << 17)) & 0xFFFFFFFF
    p = (p + (p << 7)) & 0xFFFFFFFF
    p = (p + (p << 4)) & 0xFFFFFFFF
    p ^= p >> 5
    p = (p + (p << 16)) & 0xFFFFFFFF
    p ^= p >> 7
    p ^= p >> 3
    p ^= (p << 6) & 0xFFFFFFFF
    p ^= p >> 17
    return p & 0xFFFFFFFF


def select_partition(seed, x, y, z, parts, num_texels):
    if num_texels < 31:
        x <<= 1
        y <<= 1
        z <<= 1

    seed += (parts - 1) * 1024

    rnum = hash52(seed)

    seed1 = rnum & 0xF
    seed2 = (rnum >> 4) & 0xF
    seed3 = (rnum >> 8) & 0xF
    seed4 = (rnum >> 12) & 0xF
    seed5 = (rnum >> 16) & 0xF
    seed6 = (rnum >> 20) & 0xF
    seed7 = (rnum >> 24) & 0xF
    seed8 = (rnum >> 28) & 0xF
    seed9 = (rnum >> 18) & 0xF
    seed10 = (rnum >> 22) & 0xF
    seed11 = (rnum >> 26) & 0xF
    seed12 = ((rnum >> 30) | (rnum << 2)) & 0xF

    seed1 *= seed1
    seed2 *= seed2
    seed3 *= seed3
    seed4 *= seed4
    seed5 *= seed5
    seed6 *= seed6
    seed7 *= seed7
    seed8 *= seed8
    seed9 *= seed9
    seed10 *= seed10
    seed11 *= seed11
    seed12 *= seed12

    if seed & 1:
        sh1 = 4 if (seed & 2) else 5
        sh2 = 6 if (parts == 3) else 5
    else:
        sh1 = 6 if (parts == 3) else 5
        sh2 = 4 if (seed & 2) else 5

    sh3 = sh1 if (seed & 0x10) else sh2

    seed1 >>= sh1
    seed2 >>= sh2
    seed3 >>= sh1
    seed4 >>= sh2
    seed5 >>= sh1
    seed6 >>= sh2
    seed7 >>= sh1
    seed8 >>= sh2
    seed9 >>= sh3
    seed10 >>= sh3
    seed11 >>= sh3
    seed12 >>= sh3

    a = (seed1 * x + seed2 * y + seed11 * z + (rnum >> 14)) & 0x3F
    b = (seed3 * x + seed4 * y + seed12 * z + (rnum >> 10)) & 0x3F
    c = (seed5 * x + seed6 * y + seed9 * z + (rnum >> 6)) & 0x3F
    d = (seed7 * x + seed8 * y + seed10 * z + (rnum >> 2)) & 0x3F

    if parts < 4:
        d = 0
    if parts < 3:
        c = 0

    if a >= b and a >= c and a >= d:
        return 0
    elif b >= c and b >= d:
        return 1
    elif c >= d:
        return 2
    else:
        return 3


def generate_binary_lut(partition_count, filename):
    lut = np.zeros(1024, dtype=np.uint32)
    for seed in range(1024):
        partition_map = [
            select_partition(seed, x, y, 0, partition_count, 16)
            for y in range(4)
            for x in range(4)
        ]
        mask_int = 0
        for i in range(len(partition_map)):
            mask_int |= partition_map[i] << (2 * i)

        lut[seed] = mask_int
    with open(filename, "wb") as f:
        print(lut.tobytes()[4 * 17 : 4 * 18])
        f.write(lut.astype(np.uint32).tobytes())


generate_binary_lut(2, "lut2_packed.bin")
