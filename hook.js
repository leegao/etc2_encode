// Frida hook to intercept cmpbe_v2_compile_multiple_shaders and dump the Valhal ISA bitcode (in MBS2X format)
// Usage:
// frida -f malioc -l hook.js -- -c Mali-G615 --vulkan astc_enc.raw.spv

// libMali-Gxx_r55p0-00rel0.so is not loaded at DT_NEEDED time, so we need to wait for it to be loaded...
function waitForModule(moduleName, callback) {
    const interval = setInterval(() => {
        const modules = Process.enumerateModules();
        const target = modules.find((m) => m.name === moduleName);

        if (target) {
            clearInterval(interval);
            callback(target.base);
        }
    }, 0);
}

const moduleName = "libMali-Gxx_r55p0-00rel0.so"; // this is an x86_64 library, dynamically loaded
const cmpbe_v2_compile_multiple_shaders = 0x001c8400; // offset of cmpbe_v2_compile_multiple_shaders
const cmpbe_v2_deserialize_MBS2_to_C = 0x001cada0; // cmpbe_v2_deserialize_MBS2_to_C

waitForModule(moduleName, (moduleBase) => {
    if (moduleBase !== null) {
        const targetAddress = moduleBase.add(cmpbe_v2_compile_multiple_shaders);
        console.log(
            `\n[Frida] libMali-Gxx_r55p0-00rel0.so is at: ${moduleBase}`,
        );
        console.log(
            `[Frida] cmpbe_v2_compile_multiple_shaders: ${targetAddress}`,
        );
        Interceptor.attach(targetAddress, {
            onEnter: function (args) {
                console.log("[Frida] cmpbe_v2_compile_multiple_shaders called");
                this.context_ptr = args[0]; // used for call to cmpbe_v2_deserialize_MBS2_to_C
                this.shader_count = args[1].toInt32();
                const rsp = this.context.rsp; // stack arguments
                this.out_compiled_program_ptr_ptr = rsp.add(40).readPointer();
            },
            onLeave: function (retval) {
                console.log(
                    "[Frida] cmpbe_v2_compile_multiple_shaders returning",
                );
                if (
                    retval.toInt32() === 0 &&
                    this.out_compiled_program_ptr_ptr !== null
                ) {
                    try {
                        const out_program =
                            this.out_compiled_program_ptr_ptr.readPointer();
                        const stride = 72;
                        for (let i = 0; i < this.shader_count; i++) {
                            const elementBase = out_program.add(i * stride);
                            // Call deserialize_MBS2_to_C
                            const fakeStreamObj = Memory.alloc(stride);
                            Memory.copy(fakeStreamObj, elementBase, stride);
                            const out_deserialized_ptr_ptr = Memory.alloc(
                                Process.pointerSize,
                            );

                            const deserialize_MBS2_to_C = new NativeFunction(
                                moduleBase.add(cmpbe_v2_deserialize_MBS2_to_C),
                                "uint64",
                                ["pointer", "pointer", "pointer"],
                            );
                            const status = deserialize_MBS2_to_C(
                                this.context_ptr,
                                fakeStreamObj,
                                out_deserialized_ptr_ptr,
                            );

                            if (status == 0) {
                                const finalCStrPtr =
                                    out_deserialized_ptr_ptr.readPointer();
                                if (!finalCStrPtr.isNull()) {
                                    const decompiledCodeOutput =
                                        finalCStrPtr.readUtf8String();
                                    File.writeAllText(
                                        "astc_enc_mbs2_shader.h",
                                        `#include "cmpbe_chunks.h"\n` +
                                            decompiledCodeOutput,
                                    );
                                }
                            }
                        }
                    } catch (err) {
                        console.log(
                            `[Frida] Failed to parse output_program: ${err}`,
                        );
                    }
                }
            },
        });
    } else {
        console.log(`[Frida] Cannot find ${moduleName}`);
    }
});
