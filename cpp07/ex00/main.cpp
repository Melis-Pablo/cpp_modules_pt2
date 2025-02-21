#include <iostream>
#include <string>
#include "whatever.hpp"

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

int main(void) {
    // Subject PDF Tests
    {
        printHeader("Subject PDF Tests");

        int a = 2;
        int b = 3;

        ::swap(a, b);
        std::cout << "a = " << a << ", b = " << b << std::endl;
        std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
        std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

        std::string c = "chaine1";
        std::string d = "chaine2";

        ::swap(c, d);
        std::cout << "c = " << c << ", d = " << d << std::endl;
        std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
        std::cout << "max(c, d) = " << ::max(c, d) << std::endl;
    }

    // Basic Functionality Tests
    {
        printHeader("Basic Functionality Tests");

        // Integer tests
        int x = 42;
        int y = 21;

        ::swap(x, y);
        printTestResult("Integer swap", x == 21 && y == 42);
        printTestResult("Integer min", ::min(x, y) == 21);
        printTestResult("Integer max", ::max(x, y) == 42);
    }

    // Equal Values Tests
    {
        printHeader("Equal Values Tests");

        int a = 42;
        int b = 42;
        const int& minResult = ::min(a, b);
        const int& maxResult = ::max(a, b);

        printTestResult("Equal values min returns second argument", &minResult == &b);
        printTestResult("Equal values max returns second argument", &maxResult == &b);
    }

    // Different Types Tests
    {
        printHeader("Different Types Tests");

        // Float tests
        float f1 = 3.14f;
        float f2 = 2.718f;
        ::swap(f1, f2);
        printTestResult("Float swap", f1 == 2.718f && f2 == 3.14f);

        // Double tests
        double d1 = 1.111;
        double d2 = 2.222;
        printTestResult("Double min", ::min(d1, d2) == 1.111);
        printTestResult("Double max", ::max(d1, d2) == 2.222);

        // Char tests
        char c1 = 'a';
        char c2 = 'z';
        printTestResult("Char min", ::min(c1, c2) == 'a');
        printTestResult("Char max", ::max(c1, c2) == 'z');
    }

    // Reference Integrity Tests
    {
        printHeader("Reference Integrity Tests");

        int original1 = 5;
        int original2 = 10;
        const int& ref = ::min(original1, original2);

        printTestResult("Min returns reference to original value", &ref == &original1);

        const int& maxRef = ::max(original1, original2);
        printTestResult("Max returns reference to original value", &maxRef == &original2);
    }

    return 0;
}