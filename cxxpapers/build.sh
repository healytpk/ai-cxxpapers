#!/bin/sh
if [ ! -d ../build ]; then
    cd ..
    cmake -B build \
        -DBUILD_SHARED_LIBS=OFF \
        -DLLAMA_CURL=OFF        \
        -DLLAMA_BUILD_COMMON=ON -DLLAMA_BUILD_EXAMPLES=OFF -DLLAMA_BUILD_SERVER=OFF -DLLAMA_BUILD_TESTS=OFF -DLLAMA_BUILD_TOOLS=OFF
    cmake --build build --config Release
    cd -
fi

g++ -o embed -x c++ embedding.cpp.STANDALONE -x none -std=c++23 \
    -static-libstdc++ -static-libgcc           \
    -I../include/ -I../ggml/include/ -I../common/ \
    ../build/common/libcommon.a                \
    ../build/src/libllama.a                    \
    ../build/ggml/src/libggml.a                \
    ../build/ggml/src/libggml-cpu.a            \
    ../build/ggml/src/libggml-base.a           \
    /usr/lib/gcc/x86_64-linux-gnu/13/libgomp.a

g++ -o prog *.cpp -std=c++23                   \
    `wx-config --libs` `wx-config --cxxflags`  \
    -static-libstdc++ -static-libgcc           \
    -I../include/ -I../ggml/include/           \
    ../build/src/libllama.a                    \
    ../build/ggml/src/libggml.a                \
    ../build/ggml/src/libggml-cpu.a            \
    ../build/ggml/src/libggml-base.a           \
    /usr/lib/gcc/x86_64-linux-gnu/13/libgomp.a

echo "Libraries needed by 'embed': "
readelf -a ./embed | grep "(NEEDED)"

echo
echo "Libraries needed by 'prog':"
readelf -a ./prog | grep "(NEEDED)"
