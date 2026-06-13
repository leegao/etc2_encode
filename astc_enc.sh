# echo "Compiling compress.slang to compress.comp (GLSL)"
slangc astc_enc.slang -target glsl -line-directive-mode none -D ENABLE_DIAGNOSTICS1 -D DISABLE_RECONSTRUCTION1 > astc_enc.comp

echo "Compiling astc_enc.slang to astc_enc.spv (SPIR-V)"
slangc astc_enc.slang -profile glsl_450 -target spirv -o astc_enc.spv -D ENABLE_DIAGNOSTICS -D DISABLE_RECONSTRUCTION1 -entry main
spirv-dis astc_enc.spv > astc_enc.spvasm

echo "Compiling astc_enc.comp to SPIR-V"
glslc -c astc_enc.comp -o astc_enc.raw.spv
xxd -i astc_enc.spv > astc_enc.h

echo "Building..."
g++ astc_enc.cpp -lvulkan -I include -L lib -l ktx -o astc_enc.out

echo "Running..."
LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH ./astc_enc.out
