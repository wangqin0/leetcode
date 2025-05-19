# LeetCode C++ Solutions

This repository contains C++ solutions to LeetCode problems, built and managed with CMake. It also demonstrates usage of C++20 modules with a simple linked list cycle detection example.

## Prerequisites

- CMake 3.20 or higher
- C++20 compatible compiler (Clang or GCC)
- Unix-like environment or Windows with a supported shell

## Getting Started

```bash
git clone https://github.com/wangqin0/leetcode
cd leetcode
cmake --preset default
```

## Building & Running

After configuring, build and run individual targets.

### Unix

```bash
LC_TARGET=141_LinkedListCycle
cmake --build ./build --target "$LC_TARGET"
./build/src/"$LC_TARGET"
```

### Windows (PowerShell / CMD)

```powershell
$env:LC_TARGET = '141_LinkedListCycle'
cmake --build build --target $env:LC_TARGET
.\build\src\$env:LC_TARGET
```

Replace `141_LinkedListCycle` with any other target defined in `src/CMakeLists.txt`.

## C++20 Module Demonstration

A small script illustrates how to compile and run a C++20 module (requires Clang):

```bash
./module-test.sh
```

This will:

1. Compile the `ListNode` module interface (`src/Util/ListNode.cppm`) into a PCM.
2. Build and run the linked-list cycle example against that module.

## Directory Structure

```
.
├── CMakeLists.txt            # Root CMake configuration
├── CMakePresets.json         # CMake build presets
├── module-test.sh            # Manual C++20 module demo
├── src/                      # Problem solutions
│   ├── Util/
│   │   └── ListNode.cppm     # C++20 module interface
│   ├── 88_merge_sorted_array.cpp
│   ├── 27_remove_element.cpp
│   └── 141_LinkedListCycle.cpp
├── modules/                  # Prebuilt PCM files (for module demo)
└── modules-cache/            # Clang module cache
```