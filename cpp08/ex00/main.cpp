#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>

// Standard color definitions for all test files
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Failed tests
#define GREEN   "\033[32m"      // Passed tests
#define YELLOW  "\033[33m"      // Section headers
#define BLUE    "\033[34m"      // Expected exceptions/warnings
#define CYAN    "\033[36m"      // Informational output

// Standard test utility functions
void printHeader(const std::string& header) {
    std::cout << std::endl << YELLOW << "=== " << header << " ===" << RESET << std::endl;
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? GREEN : RED) << testName << ": " << (success ? "PASS" : "FAIL") << RESET << std::endl;
}

int main() {
    // 1. Basic Functionality Tests
    {
        printHeader("Basic Functionality Tests");

        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);

        // Test finding existing value
        try {
            std::vector<int>::iterator it = easyfind(vec, 2);
            printTestResult("Find middle element", *it == 2);
        } catch(const std::exception& e) {
            printTestResult("Find middle element", false);
            std::cout << RED << "Unexpected error: " << e.what() << RESET << std::endl;
        }

        // Test finding first element
        try {
            std::vector<int>::iterator it = easyfind(vec, 1);
            printTestResult("Find first element", *it == 1);
        } catch(const std::exception& e) {
            printTestResult("Find first element", false);
            std::cout << RED << "Unexpected error: " << e.what() << RESET << std::endl;
        }

        // Test finding last element
        try {
            std::vector<int>::iterator it = easyfind(vec, 3);
            printTestResult("Find last element", *it == 3);
        } catch(const std::exception& e) {
            printTestResult("Find last element", false);
            std::cout << RED << "Unexpected error: " << e.what() << RESET << std::endl;
        }
    }

    // 2. Edge Cases
    {
        printHeader("Edge Cases");

        // Empty container test
        {
            std::vector<int> empty_vec;
            try {
                easyfind(empty_vec, 1);
                printTestResult("Empty container test", false);
            } catch(const std::exception& e) {
                printTestResult("Empty container test", true);
                std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            }
        }

        // Single element container
        {
            std::vector<int> single_vec;
            single_vec.push_back(42);
            try {
                std::vector<int>::iterator it = easyfind(single_vec, 42);
                printTestResult("Single element container", *it == 42);
            } catch(const std::exception& e) {
                printTestResult("Single element container", false);
                std::cout << RED << "Unexpected error: " << e.what() << RESET << std::endl;
            }
        }

        // Duplicate values
        {
            std::vector<int> dup_vec;
            dup_vec.push_back(1);
            dup_vec.push_back(2);
            dup_vec.push_back(2);
            dup_vec.push_back(2);
            dup_vec.push_back(3);
            try {
                std::vector<int>::iterator it = easyfind(dup_vec, 2);
                printTestResult("First occurrence of duplicate",
                              std::distance(dup_vec.begin(), it) == 1);
            } catch(const std::exception& e) {
                printTestResult("First occurrence of duplicate", false);
                std::cout << RED << "Unexpected error: " << e.what() << RESET << std::endl;
            }
        }
    }

    // 3. Error Handling
    {
        printHeader("Error Handling");

        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);

        // Test non-existing value
        try {
            easyfind(vec, 999);
            printTestResult("Non-existing value exception", false);
        } catch(const std::exception& e) {
            printTestResult("Non-existing value exception", true);
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
        }

        // Test with negative values
        try {
            vec.push_back(-5);
            std::vector<int>::iterator it = easyfind(vec, -5);
            printTestResult("Find negative value", *it == -5);
        } catch(const std::exception& e) {
            printTestResult("Find negative value", false);
            std::cout << RED << "Unexpected error: " << e.what() << RESET << std::endl;
        }
    }

    // 4. Different Container Types
    {
        printHeader("Container Type Compatibility");

        // Test with std::list
        {
            std::list<int> lst;
            lst.push_back(1);
            lst.push_back(2);
            lst.push_back(3);
            lst.push_back(4);
            lst.push_back(5);
            try {
                std::list<int>::iterator it = easyfind(lst, 3);
                printTestResult("std::list compatibility", *it == 3);
            } catch(const std::exception& e) {
                printTestResult("std::list compatibility", false);
                std::cout << RED << "Error: " << e.what() << RESET << std::endl;
            }
        }

        // Test with std::deque
        {
            std::deque<int> deq;
            deq.push_back(1);
            deq.push_back(2);
            deq.push_back(3);
            deq.push_back(4);
            deq.push_back(5);
            try {
                std::deque<int>::iterator it = easyfind(deq, 3);
                printTestResult("std::deque compatibility", *it == 3);
            } catch(const std::exception& e) {
                printTestResult("std::deque compatibility", false);
                std::cout << RED << "Error: " << e.what() << RESET << std::endl;
            }
        }
    }

    // 5. Performance Test (Optional)
    {
        printHeader("Performance Test");

        std::vector<int> large_vec;
        for(int i = 0; i < 10000; ++i) {
            large_vec.push_back(i);
        }

        try {
            std::vector<int>::iterator it = easyfind(large_vec, 9999);
            printTestResult("Large container test (10000 elements)", *it == 9999);
        } catch(const std::exception& e) {
            printTestResult("Large container test (10000 elements)", false);
            std::cout << RED << "Error: " << e.what() << RESET << std::endl;
        }
    }

    return 0;
}