#include <iostream>
#include <memory>

#include "ft_memory.h"


void test_std_unique_ptr() {
    std::unique_ptr<int> stdPtr = std::make_unique<int>(42);
    std::cout << "std::unique_ptr value: " << *stdPtr << std::endl;
}

void test_ft_unique_ptr() {
    ft::unique_ptr<int> ftPtr = ft::make_unique<int>(42); // Assuming ft::make_unique exists
    std::cout << "ft::unique_ptr value: " << *ftPtr << std::endl;
}

void test_std_unique_ptr_array() {
    std::unique_ptr<int[]> stdArray = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        stdArray[i] = i * 10;
    }
    std::cout << "std::unique_ptr array values: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << stdArray[i] << " ";
    }
    std::cout << std::endl;
}

void test_ft_unique_ptr_array() {
    ft::unique_ptr<int[]> ftArray = ft::make_unique<int[]>(5); // Assuming ft::make_unique supports arrays
    for (int i = 0; i < 5; ++i) {
        ftArray[i] = i * 10;
    }
    std::cout << "ft::unique_ptr array values: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << ftArray[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Testing std::unique_ptr:" << std::endl;
    test_std_unique_ptr();

    std::cout << "\nTesting ft::unique_ptr:" << std::endl;
    test_ft_unique_ptr();

    std::cout << "\nTesting std::unique_ptr with arrays:" << std::endl;
    test_std_unique_ptr_array();

    std::cout << "\nTesting ft::unique_ptr with arrays:" << std::endl;
    test_ft_unique_ptr_array();

    return 0;
}