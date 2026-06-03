import astc_pack;
import encoder_utils;

[[vk::binding(0, 0)]]
StructuredBuffer<uint> input_rgba8_buffer;

[[vk::binding(1, 0)]]
RWStructuredBuffer<uint4> astc_blocks;

typedef uint8_t4[16] Reconstruction;
#ifdef ENABLE_DIAGNOSTICS
struct ASTCParameters {
  uint32_t ep0;
  uint32_t ep1;
  uint8_t weights[16];
  uint astc_seed;
  uint partition_map;
};

struct Diagnostics {
  uint2 start_time;
  float mse;
  uint unused;
#ifndef DISABLE_RECONSTRUCTION
  Reconstruction reconstructed;
#else
  uint reconstructed[16];
#endif
  ASTCParameters params;
};

[[vk::binding(2, 0)]]
RWStructuredBuffer<Diagnostics> diagnostics;
#endif

[[vk::binding(3, 0)]]
StructuredBuffer<uint> lut2;

[[vk::binding(4, 0)]]
StructuredBuffer<uint> astc_2p_lut_s2;

float reconstruct(uint3 ep0, uint3 ep1, uint weights[16]) {
  float mse = 0.0;
  for (uint i = 0; i < 16; i++) {
    int3 C = pixels[i];
    int3 reconstructed =
        int3(clamp(lerp(ep0, ep1, float(weights[i]) / 255.0), 0, 255));
#ifdef ENABLE_DIAGNOSTICS
#ifndef DISABLE_RECONSTRUCTION
    diagnostics[buffer_index].reconstructed[i] =
        uint8_t4(uint8_t3(reconstructed), 255);
#endif
#endif
    var err = (C - reconstructed) / 255.0;
    mse += dot(err, err);
  }
#ifdef ENABLE_DIAGNOSTICS
  diagnostics[buffer_index].mse = mse / 3.0 / 16.0;
#endif
  return mse / 3.0 / 16.0;
}

float reconstruct_2p(uint3 ep0, uint3 ep1, uint3 ep2, uint3 ep3,
                     uint weights[16], PartitionMap partition_map) {
  float mse = 0.0;
  for (uint i = 0; i < 16; i++) {
    let partition = partition_map[i];
    int3 C = pixels[i];
    int3 reconstructed =
        int3(clamp(lerp(ep0, ep1, float(weights[i]) / 255.0), 0, 255));
    if (partition == 1) {
      reconstructed =
          int3(clamp(lerp(ep2, ep3, float(weights[i]) / 255.0), 0, 255));
    }
#ifdef ENABLE_DIAGNOSTICS
#ifndef DISABLE_RECONSTRUCTION
    diagnostics[buffer_index].reconstructed[i] =
        uint8_t4(uint8_t3(reconstructed), 255);
#endif
#endif
    var err = (C - reconstructed) / 255.0;
    mse += dot(err, err);
  }
#ifdef ENABLE_DIAGNOSTICS
  diagnostics[buffer_index].mse = mse / 3.0 / 16.0;
#endif
  return mse / 3.0 / 16.0;
}

struct Flags {
  PackedArray<1, 32> flags;
  property bool use_aabb {
    get { return bool(flags[0]); }
  }
  property bool try_2p {
    get { return bool(flags[1]); }
  }
};

struct PushConstants {
  int2 u_TextureDimensions;
  Flags u_Flags;
};

[[vk::push_constant]]
PushConstants pushConstants;

static uint buffer_index;
static uint3 pixels[16];

extension uint3 {
  half3 to_unorm() { return half3(this) / 255.0h; }
}

void solve_weights(PartitionMap partition_map, int partition, half3 ep0,
                   half3 ep1, out uint weights[16]) {
  let L = ep1 - ep0;
  let invLenSq = 1.0h / (dot(L, L) + 0.000001h);
  for (int i = 0; i < 16; i++) {
    if (partition_map[i] != partition)
      continue;
    let C = pixels[i].to_unorm();
    let pDotL = dot(C - ep0, L);
    let w = pDotL * invLenSq;
    weights[i] = uint(saturate(w) * 255);
  }
}

void encode_block_AABB(out uint3 endpoint_start, out uint3 endpoint_end,
                       out uint weights[16]) {
  uint min_r = 255, min_g = 255, min_b = 255;
  uint max_r = 0, max_g = 0, max_b = 0;
  for (int i = 0; i < 16; i++) {
    min_r = min(min_r, pixels[i].x);
    min_g = min(min_g, pixels[i].y);
    min_b = min(min_b, pixels[i].z);
    max_r = max(max_r, pixels[i].x);
    max_g = max(max_g, pixels[i].y);
    max_b = max(max_b, pixels[i].z);
  }

  endpoint_start = uint3(min_r, min_g, min_b);
  endpoint_end = uint3(max_r, max_g, max_b);
  var ep0 = half3(endpoint_start) / 255.0h;
  var ep1 = half3(endpoint_end) / 255.0h;
  PartitionMap partition_map = PartitionMap( {});
  solve_weights(partition_map, 0, ep0, ep1, weights);
}

void find_best_eps_via_pca(const PartitionMap partition_map, uint partition,
                           out half3 ep0, out half3 ep1) {
  half3 axis = half3(0.17h, 0.83h, 0.38h);
  half3 centroid = half3(0);
  uint count = 0;

  for (uint i = 0; i < 16; i++) {
    if (partition_map[i] != partition)
      continue;
    centroid += pixels[i].to_unorm();
    count += 1;
  }
  centroid /= half(count);

  if (count == 0) {
    ep0 = half3(0.0h);
    ep1 = half3(0.0h);
    return;
  }

  if (count == 1) {
    ep0 = saturate(centroid);
    ep1 = saturate(centroid);
    return;
  }

  half3x3 C = (half3x3)0;
  for (uint i = 0; i < 16; i++) {
    if (partition_map[i] != partition)
      continue;
    half3 d = pixels[i].to_unorm() - centroid;
    C[0] += d.x * d; // Row 0: [xx, xy, xz]
    C[1] += d.y * d; // Row 1: [yx, yy, yz]
    C[2] += d.z * d; // Row 2: [zx, zy, zz]
  }
  C /= half(count);

  // Check for degenerate cases of single color (low trace of C)
  var trace = C[0].x + C[1].y + C[2].z;
  if (trace < 3e-4) {
    ep0 = saturate(centroid);
    ep1 = saturate(centroid);
    return;
  }

  for (int iter = 0; iter < 4; iter++) {
    axis = mul(C, axis);
    var lenSq = dot(axis, axis);
    if (lenSq > 1e-8) {
      axis *= rsqrt(lenSq);
    }
  }

  // The data is isotropic (C ~ I), so any direction passing through the
  // centroid is valid
  if (dot(axis, axis) < 1e-8) {
    ep0 = saturate(centroid);
    ep1 = saturate(pixels[0].to_unorm());
    return;
  }

  axis = normalize(axis);
  var min_t = 1000.0h;
  var max_t = -1000.0h;

  for (int i = 0; i < 16; i++) {
    if (partition_map[i] != partition)
      continue;
    var d = half3(pixels[i]) / 255.0h - centroid;
    var t = dot(d, axis);
    min_t = min(min_t, t);
    max_t = max(max_t, t);
  }

  ep0 = saturate(centroid + axis * (min_t));
  ep1 = saturate(centroid + axis * (max_t));
}

void encode_block(out uint3 ep0_u8, out uint3 ep1_u8, out uint weights[16]) {
  half3 ep0 = half3(0.0h);
  half3 ep1 = half3(0.0h);
  PartitionMap partition_map = PartitionMap( {});
  find_best_eps_via_pca(partition_map, 0, ep0, ep1);
  // 99.9% of the time, this will catch blue contract
  if (ep1.x + ep1.y + ep1.z < ep0.x + ep0.y + ep0.z) {
    var temp = ep0;
    ep0 = ep1;
    ep1 = temp;
  }

  ep0_u8 = uint3(ep0 * 255.0h);
  ep1_u8 = uint3(ep1 * 255.0h);
  solve_weights(partition_map, 0, ep0, ep1, weights);
  return;
}

typedef PackedArray<2, 16> PartitionMap;

void kmeans<let max_partitions : int>(out PartitionMap partition_map) {
  half3 centroids[max_partitions];
  PackedArray<8, max_partitions> partition_counts;

  for (uint k = 0; k < max_partitions; k++) {
    centroids[k] = pixels[(k * 4) % 16].to_unorm();
  }

  for (uint iter = 0; iter < 3; iter++) {
    // Reset counts
    for (uint c = 0; c < max_partitions; c++)
      partition_counts[c] = 0;

    for (uint i = 0; i < 16; i++) {
      var p = pixels[i].to_unorm();

      var best_dist = 1000.0h;
      uint best_centroid = 0;

      // Nearest centroid through projection
      for (uint centroid = 0; centroid < max_partitions; centroid++) {
        var delta = p - centroids[centroid];
        var d = dot(delta, delta);
        if (d < best_dist) {
          best_dist = d;
          best_centroid = centroid;
        }
      }

      partition_map[i] = best_centroid;
      partition_counts[best_centroid]++;
    }

    var changed_map = false;
    for (uint p = 0; p < max_partitions; p++) {
      if (partition_counts[p] == 0) {
        // Steal a pixel from another partition to restart this one
        uint steal_idx = (p * 4 + 1) % 16;
        uint victim_p = partition_map[steal_idx];
        if (partition_counts[victim_p] > 1) {
          partition_map[steal_idx] = p;
          partition_counts[p]++;
          partition_counts[victim_p]--;
          changed_map = true;
        }
      }
    }

    // Update centroids
    if (iter < 2 || changed_map) {
      half3 new_sums[max_partitions] = {};
      for (uint i = 0; i < 16; i++) {
        var p = pixels[i].to_unorm();
        var idx = partition_map[i];
        new_sums[idx] += p;
      }
      for (uint centroid = 0; centroid < max_partitions; centroid++) {
        var count = partition_counts[centroid];
        if (count != 0) {
          centroids[centroid] = new_sums[centroid] / half(count);
        }
      }
    }
  }
}

uint get_closest_seed2(uint input, out uint final_pattern) {
  uint key = canonicalize_lut2(input);
  uint seed = (astc_2p_lut_s2[key / 3] >> ((key % 3) * 10)) & 0x3FF;
  final_pattern = lut2[seed];
  return seed;
}

void snap(inout PartitionMap partition_map, out uint astc_seed) {
  static_assert(partition_map.kStorageCount == 1,
                "PartitionMap must have exactly 1 storage element");

  var raw_map = partition_map.data[0];
  uint final_mask;
  astc_seed = get_closest_seed2(raw_map, final_mask);
  partition_map.data[0] = final_mask;
}

void encode_block_2p(out uint3 ep0_u8, out uint3 ep1_u8, out uint3 ep2_u8,
                     out uint3 ep3_u8, out uint weights[16],
                     out PartitionMap partition_map, out uint astc_seed) {
  half3 ep0 = half3(0.0h);
  half3 ep1 = half3(0.0h);
  half3 ep2 = half3(0.0h);
  half3 ep3 = half3(0.0h);

  kmeans<2>(partition_map);
  snap(partition_map, astc_seed);
  find_best_eps_via_pca(partition_map, 0, ep0, ep1);
  find_best_eps_via_pca(partition_map, 1, ep2, ep3);
  // 99.9% of the time, this will catch blue contract
  if (ep1.x + ep1.y + ep1.z < ep0.x + ep0.y + ep0.z) {
    var temp = ep0;
    ep0 = ep1;
    ep1 = temp;
  }
  if (ep3.x + ep3.y + ep3.z < ep2.x + ep2.y + ep2.z) {
    var temp = ep2;
    ep2 = ep3;
    ep3 = temp;
  }

  ep0_u8 = uint3(ep0 * 255.0h);
  ep1_u8 = uint3(ep1 * 255.0h);
  ep2_u8 = uint3(ep2 * 255.0h);
  ep3_u8 = uint3(ep3 * 255.0h);
  solve_weights(partition_map, 0, ep0, ep1, weights);
  solve_weights(partition_map, 1, ep2, ep3, weights);
  return;
}

void swap_endpoints(inout uint3 ep0, inout uint3 ep1, inout uint weights[16]) {
  // See Table C.2.17
  var temp = ep0;
  ep0 = ep1;
  ep1 = temp;
  for (int i = 0; i < 16; i++) {
    weights[i] = clamp(255 - int(weights[i]), 0, 255);
  }
}

uint quantize(inout uint3 ep0, inout uint3 ep1, inout uint weights[16]) {
  // TODO: find an optimal quant mode
  var quant_weight_mode = 8u;
  var quant_ep_mode = get_quant_ep_mode(quant_weight_mode, 16, 6, 1);
  quantize_u8(ep0, ENDPOINT_MAX_VALUES[quant_ep_mode]);
  quantize_u8(ep1, ENDPOINT_MAX_VALUES[quant_ep_mode]);
  if (will_blue_contract(ep0, ep1, quant_ep_mode))
    swap_endpoints(ep0, ep1, weights);
  quantize_u8(weights, WEIGHT_MAX_VALUES[quant_weight_mode]);
  return quant_weight_mode;
}

uint quantize(inout uint3 ep0, inout uint3 ep1, inout uint3 ep2,
              inout uint3 ep3, inout uint weights[16]) {
  // TODO: find an optimal quant mode
  var quant_weight_mode = 4u;
  var quant_ep_mode = get_quant_ep_mode(quant_weight_mode, 16, 12, 2);
  quantize_u8(ep0, ENDPOINT_MAX_VALUES[quant_ep_mode]);
  quantize_u8(ep1, ENDPOINT_MAX_VALUES[quant_ep_mode]);
  quantize_u8(ep2, ENDPOINT_MAX_VALUES[quant_ep_mode]);
  quantize_u8(ep3, ENDPOINT_MAX_VALUES[quant_ep_mode]);
  if (will_blue_contract(ep0, ep1, quant_ep_mode))
    swap_endpoints(ep0, ep1, weights);
  if (will_blue_contract(ep2, ep3, quant_ep_mode))
    swap_endpoints(ep2, ep3, weights);
  quantize_u8(weights, WEIGHT_MAX_VALUES[quant_weight_mode]);
  return quant_weight_mode;
}

[shader("compute")]
[numthreads(8, 8, 1)]
void main(uint3 gl_GlobalInvocationID: SV_DispatchThreadID) {
  int2 block_pos = int2(gl_GlobalInvocationID.xy);
  int2 tex_coord = block_pos * 4;

#ifdef ENABLE_DIAGNOSTICS
  uint2 startTime = clockRealtime2x32EXT();
#endif

  if (any(tex_coord >= pushConstants.u_TextureDimensions))
    return;

  buffer_index =
      block_pos.y * (pushConstants.u_TextureDimensions.x / 4) + block_pos.x;

  // Encoding
  uint width = pushConstants.u_TextureDimensions.x;
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      uint r, g, b, a;

      var tex_coord = (tex_coord.y + y) * width + (tex_coord.x + x);
      var tex_element = input_rgba8_buffer[tex_coord];
      a = (tex_element >> 24) & 0xFFu;
      b = (tex_element >> 16) & 0xFFu;
      g = (tex_element >> 8) & 0xFFu;
      r = (tex_element >> 0) & 0xFFu;

      pixels[y * 4 + x] = uint3(r, g, b);
    }
  }

  //   uint3 ep0, ep1;
  //   uint weights[16];
  //   encode_block(ep0, ep1, weights);
  //   var quant_weight_mode = quantize(ep0, ep1, weights);

  // #ifdef ENABLE_DIAGNOSTICS
  //   reconstruct(ep0, ep1, weights);
  // #endif

  //   uint4 eps[2];
  //   eps[0] = uint4(ep0, 255);
  //   eps[1] = uint4(ep1, 255);
  //   var packed =
  //       pack_astc_4x4_block<1>(eps, weights, quant_weight_mode, 0u, false);

  uint3 ep0, ep1, ep2, ep3;
  uint weights[16];
  PartitionMap partition_map;
  uint astc_seed;
  encode_block_2p(ep0, ep1, ep2, ep3, weights, partition_map, astc_seed);
  var quant_weight_mode = quantize(ep0, ep1, ep2, ep3, weights);

#ifdef ENABLE_DIAGNOSTICS
  reconstruct_2p(ep0, ep1, ep2, ep3, weights, partition_map);
#endif

  uint4 eps[4];
  eps[0] = uint4(ep0, 255);
  eps[1] = uint4(ep1, 255);
  eps[2] = uint4(ep2, 255);
  eps[3] = uint4(ep3, 255);
  var packed =
      pack_astc_4x4_block<2>(eps, weights, quant_weight_mode, astc_seed, false);

  astc_blocks[buffer_index] = packed;

#ifdef ENABLE_DIAGNOSTICS
  diagnostics[buffer_index].start_time = startTime;
  diagnostics[buffer_index].params.ep0 = ep0.x | (ep0.y << 8) | (ep0.z << 16);
  diagnostics[buffer_index].params.ep1 = ep1.x | (ep1.y << 8) | (ep1.z << 16);
  for (int i = 0; i < 16; i++) {
    diagnostics[buffer_index].params.weights[i] = uint8_t(weights[i] & 0xFFu);
  }
  diagnostics[buffer_index].params.astc_seed = astc_seed;
  diagnostics[buffer_index].params.partition_map = partition_map.data[0];
#endif
}
