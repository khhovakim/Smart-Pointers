#!/bin/bash

# Default build type
BUILD_TYPE=${1:-Debug}

# Normalize build type to lowercase for directory naming
BUILD_DIR="build/$(echo "$BUILD_TYPE" | tr '[:upper:]' '[:lower:]')"

# Clear screen (optional)
clear

# Step 1: Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo "📁 Creating build directory: $BUILD_DIR"
    mkdir -p "$BUILD_DIR"
fi

# Step 2: Run CMake configuration
echo "🛠 Configuring CMake with build type: $BUILD_TYPE"
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

# Step 3: Build the project
echo "⚙️  Building project..."
cmake --build "$BUILD_DIR"

# Step 4: Check result
if [ $? -eq 0 ]; then
    echo "✅ Build completed successfully [${BUILD_TYPE}]"
else
    echo "❌ Build failed [${BUILD_TYPE}]. Please check the output for errors."
    exit 1
fi
