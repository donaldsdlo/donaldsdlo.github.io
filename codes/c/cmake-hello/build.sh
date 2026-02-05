#!/bin/bash
# Unix/Linux/macOS build script for CMake project

set -e

echo "Building CMake Hello World Project..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# Build the project
echo "Building project..."
cmake --build .

# Copy compile_commands.json to project root for language servers
cp compile_commands.json ../compile_commands.json

echo ""
echo "Build successful! Executable: build/bin/cmake_hello"
echo "compile_commands.json generated for language server support."

cd ..
