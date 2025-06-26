#!/bin/bash

# Define variables
BUILD_DIR=build

# Optional: clear screen
clear

# Step 1: Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo "📁 Creating build directory..."
    mkdir "$BUILD_DIR"
fi

# Step 2: Run CMake configuration
echo "🛠 Running CMake..."
cmake -S . -B "$BUILD_DIR"

# Step 3: Build with Make
echo "⚙️  Building project..."
cmake --build "$BUILD_DIR"
if [ $? -eq 0 ]; then
    echo "✅ Build completed successfully."
else
    echo "❌ Build failed. Please check the output for errors."
    exit 1
fi