# Build and run C++20 module test with clang++ (Homebrew/LLVM):
# 1) prepare module cache directory
mkdir -p modules-cache/ modules/ build/

# 2) compile module interface into a PCM file
TMPDIR=modules-cache/ \
clang++ -std=c++20 \
    -fmodules -fcxx-modules \
    -fmodule-output=modules/ListNode.pcm \
    -c src/Util/ListNode.cppm

# 3) compile main, linking the prebuilt module PCM
TMPDIR=modules-cache/ \
clang++ -std=c++20 \
    -fmodules -fcxx-modules \
    -fmodules-cache-path=modules-cache/ \
    -fprebuilt-module-path=modules \
    src/141_LinkedListCycle.cpp modules/ListNode.pcm \
    -o build/main && ./build/main