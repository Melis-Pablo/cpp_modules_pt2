#include "RPN.hpp"
#include <iostream>
#include <string>

// Color definitions as per the Testing Framework
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Failed tests
#define GREEN   "\033[32m"      // Passed tests
#define YELLOW  "\033[33m"      // Section headers
#define BLUE    "\033[34m"      // Expected exceptions/warnings
#define CYAN    "\033[36m"      // Informational output

// Utility functions
void printHeader(const std::string& header) {
    std::cout << std::endl << YELLOW << "=== " << header << " ===" << RESET << std::endl;
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? GREEN : RED) << testName << ": " << (success ? "PASS" : "FAIL") << RESET << std::endl;
}

int main() {
    // PDF/Project Specific Tests
    {
        printHeader("Subject PDF Test");

        try {
            RPN rpn;
            int result = rpn.evaluate("8 9 * 9 - 9 - 9 - 4 - 1 +");
            std::cout << CYAN << "Result: " << result << RESET << std::endl;
            printTestResult("Example 1", result == 42);

            result = rpn.evaluate("7 7 * 7 -");
            std::cout << CYAN << "Result: " << result << RESET << std::endl;
            printTestResult("Example 2", result == 42);

            result = rpn.evaluate("1 2 * 2 / 2 * 2 4 - +");
            std::cout << CYAN << "Result: " << result << RESET << std::endl;
            printTestResult("Example 3", result == 0);

            try {
                result = rpn.evaluate("(1 + 1)");
                printTestResult("Example 4", false);
            } catch (const std::exception &e) {
                std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
                printTestResult("Example 4", true);
            }
        } catch (const std::exception &e) {
            std::cout << BLUE << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Subject PDF Test", false);
        }
    }

    // Basic Functionality Tests
    {
        printHeader("Basic Operations");

        try {
            RPN rpn;

            // Addition
            int result = rpn.evaluate("3 4 +");
            printTestResult("Addition", result == 7);

            // Subtraction
            result = rpn.evaluate("5 2 -");
            printTestResult("Subtraction", result == 3);

            // Multiplication
            result = rpn.evaluate("6 7 *");
            printTestResult("Multiplication", result == 42);

            // Division
            result = rpn.evaluate("8 2 /");
            printTestResult("Division", result == 4);

            // Combined operations
            result = rpn.evaluate("3 4 + 5 *");
            printTestResult("Combined Operations", result == 35);
        } catch (const std::exception &e) {
            std::cout << BLUE << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Basic Operations", false);
        }
    }

    // Edge Cases
    {
        printHeader("Edge Cases");

        RPN rpn;

        // Empty expression
        try {
            rpn.evaluate("");
            printTestResult("Empty Expression", false);
        } catch (const std::exception &e) {
            std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
            printTestResult("Empty Expression", true);
        }

        // Single number
        try {
            int result = rpn.evaluate("5");
            printTestResult("Single Number", result == 5);
        } catch (const std::exception &e) {
            std::cout << BLUE << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Single Number", false);
        }

        // Division by zero
        try {
            rpn.evaluate("5 0 /");
            printTestResult("Division by Zero", false);
        } catch (const std::exception &e) {
            std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
            printTestResult("Division by Zero", true);
        }
    }

    // Exception Handling
    {
        printHeader("Exception Handling");

        RPN rpn;

        // Invalid token
        try {
            rpn.evaluate("3 a +");
            printTestResult("Invalid Token", false);
        } catch (const std::exception &e) {
            std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
            printTestResult("Invalid Token", true);
        }

        // Insufficient operands
        try {
            rpn.evaluate("3 +");
            printTestResult("Insufficient Operands", false);
        } catch (const std::exception &e) {
            std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
            printTestResult("Insufficient Operands", true);
        }

        // Extra operands
        try {
            rpn.evaluate("3 4 5 +");
            printTestResult("Extra Operands", false);
        } catch (const std::exception &e) {
            std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
            printTestResult("Extra Operands", true);
        }

        // Number >= 10
        try {
            rpn.evaluate("10 2 +");
            printTestResult("Number >= 10", false);
        } catch (const std::exception &e) {
            std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
            printTestResult("Number >= 10", true);
        }
    }

    // Object Behavior Tests
    {
        printHeader("Object Behavior");

        // Test copy constructor and assignment operator
        try {
            RPN rpn1;
            rpn1.evaluate("3 4 +"); // Set up the stack with 7

            RPN rpn2(rpn1);
            RPN rpn3;
            rpn3 = rpn1;

            // Each evaluation should be independent since we clear the stack first
            int result1 = rpn1.evaluate("5 6 +");
            int result2 = rpn2.evaluate("7 8 +");
            int result3 = rpn3.evaluate("1 2 +");

            printTestResult("Independent Operations", result1 == 11 && result2 == 15 && result3 == 3);
        } catch (const std::exception &e) {
            std::cout << BLUE << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Object Behavior", false);
        }
    }

    return 0;
}