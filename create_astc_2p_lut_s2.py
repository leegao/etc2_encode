import os
import time

import numpy as np
import torch
import torch.nn.functional as F


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


def permutations_S2(x):
    perms = [
        [0, 1],  # 0: Identity
        [1, 0],  # 1: Swap 01
    ]
    results = []
    for p_idx, mapping in enumerate(perms):
        vec = []
        for i in range(16):
            val_x = x[i]
            vec.append(mapping[val_x])
        results.append(tuple(vec))
    return results


def generate_valid_2p_maps():
    print("Generating and filtering 1024 2-partition ASTC maps...")
    BLOCK_WIDTH, BLOCK_HEIGHT = 4, 4
    NUM_TEXELS = BLOCK_WIDTH * BLOCK_HEIGHT
    PARTS = 2

    seen_normalized_maps = set()
    valid_maps_list = []
    valid_seeds_list = []

    for seed in range(1024):
        partition_map = tuple(
            [
                select_partition(seed, x, y, 0, PARTS, NUM_TEXELS)
                for y in range(BLOCK_HEIGHT)
                for x in range(BLOCK_WIDTH)
            ]
        )
        if partition_map in seen_normalized_maps:
            continue

        # Remove the single-partition seed, this helps optimization
        # avoid a basin around 0 that's almost impossible to climb out of
        if len(set(partition_map)) == 1:
            continue

        seen_normalized_maps.add(partition_map)

        # Only store the smallest seed for the S2 equivalence class
        permutations = permutations_S2(partition_map)
        for perm in permutations:
            seen_normalized_maps.add(perm)
        valid_maps_list.append(partition_map)
        valid_seeds_list.append(seed)

    print(
        f"Found {len(valid_maps_list)} unique, valid 2-partition maps (Expected 435)."
    )

    return torch.tensor(valid_maps_list, dtype=torch.float32), torch.tensor(
        valid_seeds_list, dtype=torch.int16
    )


def create_2p_ideal_to_seed_lut_s2(
    valid_maps_tensor, valid_seeds_tensor, device, batch_size=100000
):
    total_ideal_maps = 2**16

    num_valid_maps = valid_maps_tensor.shape[0]
    print(
        f"Generating {total_ideal_maps} entries. S2 Invariance. {num_valid_maps} Valid Targets."
    )
    valid_maps_tensor = valid_maps_tensor.to(device).long()
    valid_seeds_tensor = valid_seeds_tensor.to(device)

    perms = torch.tensor(
        [
            [0, 1, 2],
            [1, 0, 2],
        ],
        device=device,
        dtype=torch.long,
    )

    # [2, N, 16]
    expanded_valid = perms[:, valid_maps_tensor]

    # Flatten: [2*N, 16]
    flat_targets = expanded_valid.reshape(-1, 16)

    valid_onehot = F.one_hot(flat_targets, num_classes=2).float()
    valid_flat_t = valid_onehot.view(flat_targets.shape[0], -1).t()  # [32, 2*N]
    powers_of_2 = (2 ** torch.arange(16, device=device, dtype=torch.int64)).unsqueeze(0)

    lut_parts = []  # accumulator

    for start in range(0, total_ideal_maps, batch_size):
        end = min(start + batch_size, total_ideal_maps)
        batch_ints = torch.arange(start, end, device=device, dtype=torch.int64)
        batch_maps = (batch_ints.unsqueeze(1) // powers_of_2) % 2
        batch_onehot = F.one_hot(batch_maps, num_classes=2).float()
        batch_flat = batch_onehot.view(batch_onehot.shape[0], -1)

        # [Batch, 2*N]
        raw_scores = torch.mm(batch_flat, valid_flat_t)

        # Reshape to [Batch, 2, N]
        scores_view = raw_scores.view(-1, 2, num_valid_maps)
        best_permutation_scores = scores_view.max(dim=1).values

        # Argmax over Seeds (dim 1)
        best_indices = torch.argmax(best_permutation_scores, dim=1)
        lut_parts.append(valid_seeds_tensor[best_indices].cpu())

        if start % (batch_size * 5) == 0:
            print(f"   Processed {end / 1_000_000:.2f}M entries...")

    return torch.cat(lut_parts)


def coalesce_lut_to_uint32(lut_tensor):
    # [Entry 0] -> bits 0-9    use & 0x3FF
    # [Entry 1] -> bits 10-19  use (>>10) & 0x3FF
    # [Entry 2] -> bits 20-29  use (>>20) & 0x3FF
    lut = lut_tensor.cpu().to(dtype=torch.int32)
    packed_view = lut.view(-1, 3)
    coalesced = (
        (packed_view[:, 0]) | (packed_view[:, 1] << 10) | (packed_view[:, 2] << 20)
    )
    return coalesced


# device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
device = "cpu"  # Dataset is so small, it's faster to avoid launching a dedicated kernel
print(f"Using device: {device}")
valid_maps_tensor, valid_seeds_tensor = generate_valid_2p_maps()
lut_ideal_to_seed = create_2p_ideal_to_seed_lut_s2(
    valid_maps_tensor, valid_seeds_tensor, device, batch_size=100000
)

file1 = "astc_2p_4x4_lut_s2.bin"
with open(file1, "wb") as f:
    # Only store first 2**5 entries since the second half are rotationally equivalent via (01)
    f.write(
        coalesce_lut_to_uint32(lut_ideal_to_seed[: 1 + 2**15])
        .numpy()
        .astype(np.uint32)
        .tobytes()
    )

print(f"\nSuccessfully generated and saved LUT to '{file1}'")
print(f"   -> Total entries: {len(lut_ideal_to_seed)}")
print(f"   -> Data type: uint32 (4 bytes per entry)")
print(f"   -> Total size: {os.path.getsize(file1)} bytes")
