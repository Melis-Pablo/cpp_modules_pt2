#include <iostream>
#include <string>
#include "Array.hpp"

// ANSI escape codes for colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

void printHeader(const std::string& header) {
    std::cout << std::endl << YELLOW << "=== " << header << " ===" << RESET << std::endl;
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? GREEN : RED) << testName << ": " << (success ? "PASS" : "FAIL") << RESET << std::endl;
}

template<typename T>
void displayArray(const Array<T>& arr) {
    std::cout << CYAN << "Array contents: ";
    for (unsigned int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << RESET << std::endl;
}

int main(void) {
    // Default Initialization Tests (from subject)
    {
        printHeader("Testing Default Initialization (Subject Example)");
        std::cout << CYAN << "Testing raw pointer initialization:" << RESET << std::endl;
        int* a = new int();
        std::cout << "Value of *a: " << *a << std::endl;
        delete a;

        std::cout << CYAN << "\nComparing with Array class initialization:" << RESET << std::endl;
        Array<int> numbers(5);
        displayArray(numbers);
    }

    // Empty Array Tests
    {
        printHeader("Empty Array Tests");
        Array<int> emptyArray;
        printTestResult("Empty array size is 0", emptyArray.size() == 0);

        try {
            emptyArray[0];
            printTestResult("Access to empty array", false);
        } catch (const std::exception& e) {
            printTestResult("Access to empty array throws exception", true);
            std::cout << BLUE << "Exception message: " << e.what() << RESET << std::endl;
        }
    }

    // Parametric Constructor Tests
    {
        printHeader("Parametric Constructor Tests");
        Array<int> numbers(5);
        printTestResult("Array size is correct", numbers.size() == 5);

        // Test element initialization
        bool allZero = true;
        for (unsigned int i = 0; i < numbers.size(); i++) {
            if (numbers[i] != 0) allZero = false;
        }
        printTestResult("Elements are zero-initialized", allZero);

        // Modify and verify elements
        for (unsigned int i = 0; i < numbers.size(); i++) {
            numbers[i] = i * 2;
        }
        displayArray(numbers);
    }

    // Copy Constructor Tests
    {
        printHeader("Copy Constructor Tests");
        Array<int> original(3);
        for (unsigned int i = 0; i < original.size(); i++) {
            original[i] = i * i;
        }
        std::cout << CYAN << "Original array:" << RESET << std::endl;
        displayArray(original);

        Array<int> copy(original);
        printTestResult("Copy has correct size", copy.size() == original.size());
        std::cout << CYAN << "Copied array:" << RESET << std::endl;
        displayArray(copy);

        // Modify copy and verify independence
        copy[0] = 999;
        printTestResult("Deep copy - original unchanged", original[0] == 0);
        printTestResult("Deep copy - copy modified", copy[0] == 999);
    }

    // Assignment Operator Tests
    {
        printHeader("Assignment Operator Tests");
        Array<int> first(3);
        Array<int> second(5); // Different size on purpose
        Array<int> *ptr = &first; // Pointer to test self-assignment

        for (unsigned int i = 0; i < first.size(); i++) {
            first[i] = i + 1;
        }

        std::cout << CYAN << "Before assignment:" << RESET << std::endl;
        std::cout << "First array: ";
        displayArray(first);
        std::cout << "Second array: ";
        displayArray(second);

        second = first;
        printTestResult("Assigned array has correct size", second.size() == first.size());
        std::cout << CYAN << "After assignment:" << RESET << std::endl;
        displayArray(second);

        // Modify second and verify independence
        second[0] = 999;
        printTestResult("Deep copy on assignment - original unchanged", first[0] == 1);
        printTestResult("Deep copy on assignment - copy modified", second[0] == 999);

        // Self assignment test through pointer to avoid warning
        *ptr = first;
        printTestResult("Self assignment handled", ptr->size() == first.size() && (*ptr)[0] == first[0]);
    }

    // Exception Handling Tests
    {
        printHeader("Exception Handling Tests");
        Array<int> arr(3);

        // Test out of bounds access
        try {
            arr[3] = 0;
            printTestResult("Out of bounds access", false);
        } catch (const std::exception& e) {
            printTestResult("Out of bounds exception caught", true);
            std::cout << BLUE << "Exception message: " << e.what() << RESET << std::endl;
        }

        // Test negative index
        try {
            arr[-1] = 0;
            printTestResult("Negative index access", false);
        } catch (const std::exception& e) {
            printTestResult("Negative index exception caught", true);
        }
    }

    // Different Types Tests
    {
        printHeader("Different Types Tests");

        // Test with strings
        Array<std::string> strings(3);
        strings[0] = "Hello";
        strings[1] = "World";
        strings[2] = "!";
        std::cout << CYAN << "String array:" << RESET << std::endl;
        displayArray(strings);

        // Test with floating point
        Array<float> floats(3);
        for (unsigned int i = 0; i < floats.size(); i++) {
            floats[i] = i + 0.5f;
        }
        std::cout << CYAN << "Float array:" << RESET << std::endl;
        displayArray(floats);

        // Test copy with strings
        Array<std::string> stringsCopy = strings;
        printTestResult("String array copy size", stringsCopy.size() == strings.size());
        printTestResult("String array copy values",
            stringsCopy[0] == "Hello" &&
            stringsCopy[1] == "World" &&
            stringsCopy[2] == "!");
    }

    // Subject PDF Test
    {
        printHeader("Subject PDF Test");
        Array<int> numbers(5);
        Array<int> mirror(numbers);
        displayArray(numbers);
        displayArray(mirror);
    }

    return 0;
}