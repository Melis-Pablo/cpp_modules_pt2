#include <iostream>
#include <string>
#include "iter.hpp"

// Color definitions for test output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

void printHeader(const std::string& header) {
    std::cout << std::endl << YELLOW << "=== " << header << " ===" << RESET << std::endl;
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? GREEN : RED) << testName << ": " << (success ? "PASS" : "FAIL") << RESET << std::endl;
}

// Test functions
template<typename T>
void displayElement(T const& element) {
    std::cout << element << " ";
}

void incrementInt(int& number) {
    number += 1;
}

void toUpperChar(char& c) {
    if (c >= 'a' && c <= 'z')
        c = c - 32;
}

bool g_functionCalled = false;
void checkFunctionCall(int const&) {
    g_functionCalled = true;
}

int main(void) {
    {
        printHeader("Basic Integer Tests");

        int arr[] = {1, 2, 3, 4, 5};
        size_t len = 5;

        std::cout << CYAN << "Original array: ";
        iter(arr, len, displayElement<int>);
        std::cout << std::endl << RESET;

        iter(arr, len, incrementInt);
        std::cout << CYAN << "After increment: ";
        iter(arr, len, displayElement<int>);
        std::cout << std::endl << RESET;

        printTestResult("Array modification",
            arr[0] == 2 && arr[1] == 3 && arr[2] == 4 && arr[3] == 5 && arr[4] == 6);
    }

    {
        printHeader("Character Array Tests");

        char str[] = "hello";
        size_t len = 5;

        std::cout << CYAN << "Original string: ";
        iter(str, len, displayElement<char>);
        std::cout << std::endl << RESET;

        iter(str, len, toUpperChar);
        std::cout << CYAN << "After toUpper: ";
        iter(str, len, displayElement<char>);
        std::cout << std::endl << RESET;

        printTestResult("String modification",
            str[0] == 'H' && str[1] == 'E' && str[2] == 'L' &&
            str[3] == 'L' && str[4] == 'O');
    }

    {
        printHeader("Edge Cases");

        // Null array test
        g_functionCalled = false;
        int* nullArr = nullptr;
        iter(nullArr, 5, checkFunctionCall);
        printTestResult("Null array handling", !g_functionCalled);

        // Empty array test
        g_functionCalled = false;
        int emptyArr[] = {};
        iter(emptyArr, 0, checkFunctionCall);
        printTestResult("Empty array handling", !g_functionCalled);

        // Single element array
        int singleArr[] = {42};
        std::cout << CYAN << "Single element array: ";
        iter(singleArr, 1, displayElement<int>);
        std::cout << std::endl << RESET;

        iter(singleArr, 1, incrementInt);
        printTestResult("Single element modification", singleArr[0] == 43);
    }

    {
        printHeader("Template Function Tests");

        double doubleArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
        std::cout << CYAN << "Double array: ";
        iter(doubleArr, 5, displayElement<double>);
        std::cout << std::endl << RESET;

        std::string strArr[] = {"Hello", "World", "!"};
        std::cout << CYAN << "String array: ";
        iter(strArr, 3, displayElement<std::string>);
        std::cout << std::endl << RESET;
    }

    {
        printHeader("Length Parameter Tests");

        int arr[] = {1, 2, 3, 4, 5};

        // Test with length = 0
        g_functionCalled = false;
        iter(arr, 0, checkFunctionCall);
        printTestResult("Zero length handling", !g_functionCalled);

        // Test with length > array size (undefined behavior, but shouldn't crash)
        std::cout << BLUE << "Warning: Testing with length > array size" << RESET << std::endl;
        std::cout << CYAN << "First 5 elements: ";
        iter(arr, 5, displayElement<int>);
        std::cout << std::endl << RESET;
    }

    return 0;
}