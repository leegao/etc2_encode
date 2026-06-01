
#ifdef ENABLE_DIAGNOSTICS
// Not available on Mali/Adreno :(
__glsl_extension(GL_EXT_shader_realtime_clock) uint2 clockRealtime2x32EXT() {
  __target_switch {
  case spirv:
    return spirv_asm {
            OpCapability ShaderClockKHR;
            OpExtension "SPV_KHR_shader_clock";
            result : $$uint2 = OpReadClockKHR Device;
        };

  case glsl:
    __intrinsic_asm "clockRealtime2x32EXT()";

  default:
    return 0;
  }
}
#endif


struct PackedArray<let M : uint, let N : uint> {
  static const uint kElementsPerStorage = 32 / M;
  static const uint kStorageCount =
      (N + kElementsPerStorage - 1u) / kElementsPerStorage;
  static const uint kMask = (1u << M) - 1u;

  uint data[kStorageCount];

  __init(uint initialValues[N]) {
    this.data = {};
    for (int n = 0; n < N; n++) {
      this[n] = initialValues[n];
    }
  }

  inline __subscript(uint n)->uint {
    get {
      var arrayIndex = n / kElementsPerStorage;
      var bitOffset = (n % kElementsPerStorage) * M;

      return (data[arrayIndex] >> bitOffset) & kMask;
    }
    set {
      var arrayIndex = n / kElementsPerStorage;
      var bitOffset = (n % kElementsPerStorage) * M;
      var clearMask = ~(kMask << bitOffset);

      data[arrayIndex] =
          (data[arrayIndex] & clearMask) | ((newValue & kMask) << bitOffset);
    }
  }
};
