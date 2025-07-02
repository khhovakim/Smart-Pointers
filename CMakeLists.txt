cmake_minimum_required(VERSION 3.16)
project(smart_ptr LANGUAGES CXX)

# ===== Compiler setup =====
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ===== Default to Debug build if not specified =====
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# ===== Compiler warnings and flags =====
set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -Wextra -Werror -pedantic-errors -fsanitize=address -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -Werror -pedantic-errors -O2")

# ===== Directories =====
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# ===== Sources =====
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.cc"
)

# ===== Header include directories =====
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
    "${INC_DIR}/*.h"
    "${INC_DIR}/*.hh"
    "${INC_DIR}/*.hpp"
)

set(INCLUDE_DIRS "")
foreach(header ${HEADER_FILES})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

# ===== Output directories =====
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)
set(CMAKE_OBJECT_PATH_MAX 4096)  # Avoid object filename too long issues

# ===== Executable =====
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

# ===== Testing support =====
enable_testing()

# Example test setup (optional)
# add_executable(test_runner test/test_main.cpp)
# add_test(NAME unit_tests COMMAND test_runner)

# ===== Install rules =====
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${INC_DIR}/ DESTINATION include FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h" PATTERN "*.hh")
