#!/bin/bash

# Set your output binary name
OUTPUT="password-manager"

# Create build directory if it doesn't exist
mkdir -p build

# Compile all .cpp files from src/ and put output in build/
g++ src/*.cpp -Iinclude -o build/$OUTPUT

# Check if build was successful
if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    echo "Run with: ./build/$OUTPUT"
else
    echo "❌ Build failed."
fi
