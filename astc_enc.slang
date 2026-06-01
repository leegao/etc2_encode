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

float decompress(const uint3 pixels[16], uint3 ep0, uint3 ep1,
                 uint weights[16]) {
  float mse = 0.0;
  for (uint8_t i = 0; i < 16; i++) {
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
  diagnostics[buffer_index].mse = mse / 16.0;
#endif
  return mse / 16.0;
}

struct Flags {
  PackedArray<1, 32> flags;
  property bool try_2p {
    get { return bool(flags[0]); }
  }
};

struct PushConstants {
  int2 u_TextureDimensions;
  Flags u_Flags;
};

[[vk::push_constant]]
PushConstants pushConstants;

static uint buffer_index;

void encode_block_AABB(const uint3 pixels[16], out uint3 endpoint_start,
                       out uint3 endpoint_end, out uint weights[16]) {
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
  let L = (half3(endpoint_end) - half3(endpoint_start)) / 255;
  let invLenSq = 1.0h / (dot(L, L) + 0.000001h);
  for (int i = 0; i < 16; i++) {
    let C = pixels[i];
    let p = 0;
    let pDotL = dot(half3(C - endpoint_start) / 255, L);
    let w = pDotL * invLenSq;
    weights[i] = uint(saturate(w) * 255);
  }
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
  uint3 pixels[16];
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

  uint3 endpoint_start, endpoint_end;
  uint weights[16];
  encode_block_AABB(pixels, endpoint_start, endpoint_end, weights);
  decompress(pixels, endpoint_start, endpoint_end, weights);

  var quant_weight_mode = 8;
  var quant_ep_mode = get_quant_ep_mode(quant_weight_mode, 16, 6, 1); // 19
  uint4 eps[2];
  eps[0] = uint4(endpoint_start, 255);
  eps[1] = uint4(endpoint_end, 255);
  var packed =
      pack_astc_4x4_block<1>(eps, weights, quant_weight_mode, 0u, false);

  astc_blocks[buffer_index] = packed;

#ifdef ENABLE_DIAGNOSTICS
  diagnostics[buffer_index].start_time = startTime;
  // diagnostics[buffer_index].mse = quant_ep_mode; // DEBUG
#endif
}
