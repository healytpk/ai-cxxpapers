#!/bin/sh
if [ ! -d ../build ]; then
    cd ..
    cmake -B build \
        -DBUILD_SHARED_LIBS=OFF \
        -DLLAMA_CURL=OFF        \
        -DLLAMA_BUILD_COMMON=ON -DLLAMA_BUILD_EXAMPLES=ON -DLLAMA_BUILD_SERVER=ON -DLLAMA_BUILD_TESTS=ON -DLLAMA_BUILD_TOOLS=ON
    cmake --build build --config Release
    cd -
fi

g++ -o tokenizer -x c++ tokenizer.cpp.STANDALONE -x none \
    -std=c++23 \
    -static-libstdc++ -static-libgcc           \
    -I/usr/include/poppler/cpp                 \
    -I../include/ -I../ggml/include/           \
    ../build/src/libllama.a                    \
    ../build/ggml/src/libggml.a                \
    ../build/ggml/src/libggml-cpu.a            \
    ../build/ggml/src/libggml-base.a           \
    /usr/lib/gcc/x86_64-linux-gnu/13/libgomp.a \
    -lgumbo -lpoppler-cpp -lcmark-gfm

g++ -o prog *.cpp                              \
    -std=c++23                                 \
    -static-libstdc++ -static-libgcc           \
    `wx-config --libs` `wx-config --cxxflags`  \
    -I../include/ -I../ggml/include/           \
    ../build/src/libllama.a                    \
    ../build/ggml/src/libggml.a                \
    ../build/ggml/src/libggml-cpu.a            \
    ../build/ggml/src/libggml-base.a           \
    /usr/lib/gcc/x86_64-linux-gnu/13/libgomp.a

echo "Libraries needed by 'tokenizer': "
readelf -a ./tokenizer | grep "(NEEDED)"

echo
echo "Libraries needed by 'prog':"
readelf -a ./prog | grep "(NEEDED)"
