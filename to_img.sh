# echo "Compiling compress.slang to compress.comp (GLSL)"
echo "Building..."
g++ to_img.cpp -lvulkan -I include -L lib -l ktx -o to_img.out

echo "Running..."
LD_LIBRARY_PATH=lib:$LD_LIBRARY_PATH ./to_img.out
