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

function getShaderPreview(srcPtr, len) {
    if (srcPtr.isNull() || len === 0) return "[NULL]";
    return (
        `[SPIRV]\n` +
        hexdump(srcPtr, {
            length: Math.min(len, 64),
            header: true,
            answers: true,
        })
    );
}

waitForModule(moduleName, (moduleBase) => {
    if (moduleBase !== null) {
        const targetAddress = moduleBase.add(cmpbe_v2_compile_multiple_shaders);
        console.log(`libMali-Gxx_r55p0-00rel0.so is at: ${moduleBase}`);
        console.log(`cmpbe_v2_compile_multiple_shaders: ${targetAddress}`);
        console.log(`\nDisassembly of cmpbe_v2_compile_multiple_shaders:`);
        let addrCursor = targetAddress;
        for (let i = 0; i < 3; i++) {
            try {
                const insn = Instruction.parse(addrCursor);
                console.log(
                    `${insn.address}: \t${insn.mnemonic}\t${insn.opStr}`,
                );
                addrCursor = insn.next;
            } catch (e) {
                break;
            }
        }

        Interceptor.attach(targetAddress, {
            onEnter: function (args) {
                console.log("\ncmpbe_v2_compile_multiple_shaders called");
                this.context_ptr = args[0]; // used for call to cmpbe_v2_deserialize_MBS2_to_C
                this.shader_count = args[1].toInt32();
                this.shader_sources = args[2];
                this.source_lengths = args[3]; // uint64_t* array

                const rsp = this.context.rsp;
                this.compilation_flags = rsp.add(8).readU32();
                this.fallback_indicator = rsp.add(16).readS32();
                this.out_compiled_program_ptr_ptr = rsp.add(40).readPointer();

                for (let i = 0; i < this.shader_count; i++) {
                    try {
                        const srcPtr = this.shader_sources
                            .add(i * 8)
                            .readPointer();
                        const len = this.source_lengths
                            .add(i * 8)
                            .readU64()
                            .toNumber();

                        console.log(`SPIRV size: ${len}`);
                        console.log(
                            hexdump(srcPtr, {
                                length: 64,
                                header: true,
                                answers: true,
                            }),
                        );
                    } catch (e) {
                        console.log(`Error parsing shader input ${e}`);
                    }
                }
            },
            onLeave: function (retval) {
                console.log(
                    `\ncmpbe_v2_compile_multiple_shaders returning: ${retval}`,
                );

                if (
                    retval.toInt32() === 0 &&
                    this.out_compiled_program_ptr_ptr !== null
                ) {
                    try {
                        const out_program =
                            this.out_compiled_program_ptr_ptr.readPointer();
                        console.log(`out_program: ${out_program}`);
                        console.log(
                            hexdump(out_program, {
                                length: 72,
                                header: true,
                                answers: true,
                            }),
                        );
                        if (out_program.isNull()) return;

                        const stride = 72; // Size of CompiledShaderEntry struct (0x48 bytes)
                        for (let i = 0; i < this.shader_count; i++) {
                            const elementBase = out_program.add(i * stride);

                            // console.log(
                            //     `@ [out_program[${i}]->free function ptr: ${elementBase.add(0x30).readPointer()}`,
                            // );

                            const bitcode_ptr = elementBase
                                .add(0x10)
                                .readPointer();
                            const length = elementBase.add(0x18).readU32();
                            console.log(
                                `Bitcode[${i}]: (size=${length})\n` +
                                    hexdump(bitcode_ptr, {
                                        length: 1024,
                                        header: true,
                                        answers: true,
                                    }),
                            );

                            // Not sure what this is
                            // const ptr1 = elementBase.add(8).readPointer();
                            // console.log(
                            //     `@ [out_program[${i}]->ptr8]:\n` +
                            //         hexdump(ptr1, {
                            //             length: 64,
                            //             header: true,
                            //             answers: true,
                            //         }),
                            // );
                            // console.log(
                            //     `@ [out_program[${i}]->ptr0x40]:\n` +
                            //         hexdump(
                            //             elementBase.add(0x40).readPointer(),
                            //             {
                            //                 length: 256,
                            //                 header: true,
                            //                 answers: true,
                            //             },
                            //         ),
                            // );
                            // console.log(
                            //     `@ [out_program[${i}]->ptr0x40->ptr0x18]:\n` +
                            //         hexdump(
                            //             elementBase
                            //                 .add(0x40)
                            //                 .readPointer()
                            //                 .add(0x18)
                            //                 .readPointer(),
                            //             {
                            //                 length: 256,
                            //                 header: true,
                            //                 answers: true,
                            //             },
                            //         ),
                            // );
                        }
                    } catch (err) {
                        console.log(`Failed to parse output_program: ${err}`);
                    }
                }
            },
        });
    } else {
        console.log(`Cannot find ${moduleName}`);
    }
});
