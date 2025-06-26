#!/bin/bash

EXECUTABLE=build/bin/smart_ptr

# Check if the executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "❌ Executable not found! Please run ./build.sh first."
    exit 1
fi

# Run the executable
echo "==========================="
echo "🚀 Running $EXECUTABLE"
echo "==========================="
echo
"$EXECUTABLE"
