slangc astc_enc.slang -target glsl -line-directive-mode none -D DISABLE_RECONSTRUCTION -D dont_UNROLL_SOLVE_WEIGHTS -D ENABLE_DEBUG_LINE_INFO > astc_enc.comp
rm astc_enc_mbs2_shader.h
frida -f ~/Downloads/Arm_Performance_Studio_2026.2/mali_offline_compiler/malioc -l hook.js -- -d -c Mali-G615 --vulkan astc_enc.comp

gcc disassemble_astc_enc.c disassemble.c -o disassemble_astc_enc.out
./disassemble_astc_enc.out
