#!/bin/bash

# Default build type
BUILD_TYPE=${1:-Debug}
BUILD_SUBDIR=$(echo "$BUILD_TYPE" | tr '[:upper:]' '[:lower:]')
EXECUTABLE="build/${BUILD_SUBDIR}/bin/smart_ptr"

# Check if the executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "❌ Executable not found at $EXECUTABLE"
    echo "💡 Hint: Try running ./build.sh $BUILD_TYPE first."
    exit 1
fi

# Run the executable
echo "=============================="
echo "🚀 Running [$BUILD_TYPE] build"
echo "=============================="
echo
"$EXECUTABLE"
