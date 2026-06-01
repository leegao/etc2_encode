# echo "Compiling compress.slang to compress.comp (GLSL)"
# slangc compress.slang -target glsl -line-directive-mode none -D ENABLE_DIAGNOSTICS1 -D DISABLE_RECONSTRUCTION1 > compress.comp

echo "Compiling astc_enc.slang to astc_enc.spv (SPIR-V)"
slangc astc_enc.slang -profile glsl_450 -target spirv -o astc_enc.spv -D ENABLE_DIAGNOSTICS -D DISABLE_RECONSTRUCTION1 -entry main
# spirv-dis compress.spv > compress.spvasm

echo "Compiling astc_enc.comp to SPIR-V"
# glslangValidator -V compress.comp -x -o compress.inc
xxd -i astc_enc.spv > astc_enc.h

echo "Building..."
g++ astc_enc.cpp -lvulkan -I include -L lib -l ktx -o astc_enc.out

echo "Running..."
LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH ./astc_enc.out
