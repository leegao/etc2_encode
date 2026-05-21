echo "Compiling compress.slang to compress.comp (GLSL)"
slangc compress.slang -target glsl > compress.comp

echo "Compiling compress.slang to compress.spv (SPIR-V)"
slangc compress.slang -profile glsl_450 -target spirv -o compress.spv -entry main
spirv-dis compress.spv > compress.spvasm

echo "Compiling compress.comp to SPIR-V"
glslangValidator -V compress.comp -x -o compress.inc
xxd -i compress.spv > compress.h

echo "Building..."
g++ main.cpp -lvulkan -I include -L lib -l ktx

echo "Running..."
LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH ./a.out
