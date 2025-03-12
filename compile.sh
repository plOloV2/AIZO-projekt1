#!/bin/bash

comp_time() {
    local start=${EPOCHREALTIME/./}
    "$@"
    local exit_code=$?
    echo >&2 "Took ~$(( (${EPOCHREALTIME/./} - start)/1000 )) ms."
    return ${exit_code}
}

# Set file locations
BIN_FILES_LOCATION="bin"

# Set compiling flags for gcc
FLAGS=(-fopenmp -lm algorithms/bubble_sort.c algorithms/heap_sort.c algorithms/insert_sort.c algorithms/merge_sort.c algorithms/quick_sort.c algorithms/select_sort.c)

# Set the source file and output binary names
SOURCE_FILE="main.c"
OUTPUT_BINARY_LINUX="apk"
OUTPUT_BINARY_WINDOWS="apk.exe"

# Check if source file is present
if [ ! -f "$SOURCE_FILE" ]; then
    echo "Error: Source file '$SOURCE_FILE' not found!"
    exit 1
fi

echo "Source file present"

DEBUG=false
CLEAN=false
WINDOWS=false
ARM=false
while [[ $# -gt 0 ]]; do
    case "$1" in
        -d|--debug)
            DEBUG=true
            shift ;;
        -c|--clean)
            CLEAN=true
            shift ;;
        -w|--windows)
            WINDOWS=true
            shift ;;
        -l|--linux)
            WINDOWS=false
            shift;;
        -a|--arm64)
            ARM=true
            shift;;
        *)
            echo "Unknown option: $1"
            exit 1 ;;
    esac
done

if $DEBUG; then
    FLAGS+=(-g)
    echo "Debug enabled."
fi

mkdir -p "$BIN_FILES_LOCATION"

if $CLEAN; then
    echo "Cleaning build directory"
    rm -rf "$BIN_FILES_LOCATION"/*
fi

if $WINDOWS; then
    FLAGS+=("algorithms/bubble_sort_x86.s")
    echo "Compiling program for Windows with flags: ${FLAGS[@]}"
    comp_time x86_64-w64-mingw32-gcc "$SOURCE_FILE" -o "$BIN_FILES_LOCATION/$OUTPUT_BINARY_WINDOWS" "${FLAGS[@]}"
else
    if $ARM; then
        FLAGS+=("algorithms/bubble_sort_aarch64.s")
        echo "Compiling program for Linux ARM with flags: ${FLAGS[@]}"
        comp_time aarch64-linux-gnu-gcc "$SOURCE_FILE" -o "$BIN_FILES_LOCATION/$OUTPUT_BINARY_LINUX" "${FLAGS[@]}"
    else 
        FLAGS+=("algorithms/bubble_sort_x86.s")
        echo "Compiling program for Linux x86 with flags: ${FLAGS[@]}"
        comp_time gcc "$SOURCE_FILE" -o "$BIN_FILES_LOCATION/$OUTPUT_BINARY_LINUX" "${FLAGS[@]}"
    fi
fi

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
else
    echo "Compilation failed."
    exit 1
fi
