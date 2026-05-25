echo "Compiling bc6.comp to SPIR-V"
glslangValidator -V bc6.comp -x -o bc6.inc

echo "Building..."
g++ decode_bc6.cpp -lvulkan -I include -L lib -l ktx -o bc6_decode

echo "Running..."
LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH ./bc6_decode
