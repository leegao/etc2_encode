import astc_pack;
import encoder_utils;

[[vk::binding(0, 0)]]
StructuredBuffer<uint> input_rgba8_buffer;

[[vk::binding(1, 0)]]
RWStructuredBuffer<uint4> astc_blocks;

typedef uint8_t4[16] Reconstruction;
#ifdef ENABLE_DIAGNOSTICS
struct Diagnostics {
  uint2 start_time;
  float mse;
  uint unused;
#ifndef DISABLE_RECONSTRUCTION
  Reconstruction reconstructed;
#else
  uint reconstructed[16];
#endif
};

[[vk::binding(2, 0)]]
RWStructuredBuffer<Diagnostics> diagnostics;
#endif

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

void solve_weights(half3 ep0, half3 ep1, out uint weights[16]) {
  let L = ep1 - ep0;
  let invLenSq = 1.0h / (dot(L, L) + 0.000001h);
  for (int i = 0; i < 16; i++) {
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
  solve_weights(ep0, ep1, weights);
}

void find_best_eps_via_pca(out half3 ep0, out half3 ep1) {
  half3 axis = half3(0.17h, 0.83h, 0.38h);
  half3 centroid = half3(0);
  uint count = 0;

  for (uint i = 0; i < 16; i++) {
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
  find_best_eps_via_pca(ep0, ep1);
  // 99.9% of the time, this will catch blue contract
  if (ep1.x + ep1.y + ep1.z < ep0.x + ep0.y + ep0.z) {
    var temp = ep0;
    ep0 = ep1;
    ep1 = temp;
  }

  ep0_u8 = uint3(ep0 * 255.0h);
  ep1_u8 = uint3(ep1 * 255.0h);
  solve_weights(ep0, ep1, weights);
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

  uint3 ep0, ep1;
  uint weights[16];
  encode_block(ep0, ep1, weights);
  var quant_weight_mode = quantize(ep0, ep1, weights);

#ifdef ENABLE_DIAGNOSTICS
  reconstruct(ep0, ep1, weights);
#endif

  uint4 eps[2];
  eps[0] = uint4(ep0, 255);
  eps[1] = uint4(ep1, 255);
  var packed =
      pack_astc_4x4_block<1>(eps, weights, quant_weight_mode, 0u, false);

  astc_blocks[buffer_index] = packed;

#ifdef ENABLE_DIAGNOSTICS
  diagnostics[buffer_index].start_time = startTime;
  // diagnostics[buffer_index].mse = quant_ep_mode; // DEBUG
#endif
}
