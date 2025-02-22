#include "Span.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <climits>

// Standard color definitions for test files
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Failed tests
#define GREEN   "\033[32m"      // Passed tests
#define YELLOW  "\033[33m"      // Section headers
#define BLUE    "\033[34m"      // Expected exceptions/warnings
#define CYAN    "\033[36m"      // Informational output

void printHeader(const std::string& header) {
    std::cout << std::endl << YELLOW << "=== " << header << " ===" << RESET << std::endl;
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? GREEN : RED) << testName << ": " << (success ? "PASS" : "FAIL") << RESET << std::endl;
}

int main() {
    // 1. Subject PDF Test
    {
        printHeader("Subject PDF Test");
        try {
            Span sp = Span(5);
            sp.addNumber(6);
            sp.addNumber(3);
            sp.addNumber(17);
            sp.addNumber(9);
            sp.addNumber(11);

            int shortest = sp.shortestSpan();
            int longest = sp.longestSpan();

            printTestResult("PDF Test - Shortest span is 2", shortest == 2);
            printTestResult("PDF Test - Longest span is 14", longest == 14);
        } catch(const std::exception& e) {
            std::cout << RED << "Unexpected error in PDF test: " << e.what() << RESET << std::endl;
        }
    }

    // 2. Basic Functionality Tests
    {
        printHeader("Basic Functionality Tests");

        // Simple span test
        try {
            Span sp(5);
            sp.addNumber(1);
            sp.addNumber(5);
            sp.addNumber(10);

            printTestResult("Basic addNumber functionality", true);
            printTestResult("Basic shortest span", sp.shortestSpan() == 4);
            printTestResult("Basic longest span", sp.longestSpan() == 9);
        } catch(const std::exception& e) {
            std::cout << RED << "Unexpected error: " << e.what() << RESET << std::endl;
        }

        // Negative numbers test
        try {
            Span sp(3);
            sp.addNumber(-5);
            sp.addNumber(0);
            sp.addNumber(5);

            printTestResult("Negative numbers - shortest span", sp.shortestSpan() == 5);
            printTestResult("Negative numbers - longest span", sp.longestSpan() == 10);
        } catch(const std::exception& e) {
            std::cout << RED << "Unexpected error: " << e.what() << RESET << std::endl;
        }
    }

    // 3. Edge Cases
    {
        printHeader("Edge Cases");

        // Empty span
        {
            Span sp(5);
            try {
                sp.shortestSpan();
                printTestResult("Empty span test", false);
            } catch(const std::exception& e) {
                printTestResult("Empty span throws exception", true);
                std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            }
        }

        // Single element
        {
            Span sp(5);
            sp.addNumber(1);
            try {
                sp.longestSpan();
                printTestResult("Single element test", false);
            } catch(const std::exception& e) {
                printTestResult("Single element throws exception", true);
                std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            }
        }

        // Integer limits
        {
            Span sp(5);
            sp.addNumber(INT_MIN);
            sp.addNumber(INT_MAX);
            try {
                long expected = static_cast<long>(INT_MAX) - INT_MIN;
                printTestResult("INT_MIN/MAX longest span", sp.longestSpan() == expected);
            } catch(const std::exception& e) {
                printTestResult("INT_MIN/MAX test", false);
                std::cout << RED << "Error: " << e.what() << RESET << std::endl;
            }
        }
    }

    // 4. Exception Handling
    {
        printHeader("Exception Handling");

        // Full span test
        {
            Span sp(2);
            try {
                sp.addNumber(1);
                sp.addNumber(2);
                sp.addNumber(3);  // Should throw
                printTestResult("Full span test", false);
            } catch(const std::exception& e) {
                printTestResult("Full span throws exception", true);
                std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            }
        }

        // Iterator range overflow
        {
            std::vector<int> numbers;
            for(int i = 0; i < 5; ++i)
                numbers.push_back(i);

            Span sp(3);  // Smaller than vector size
            try {
                sp.addNumber(numbers.begin(), numbers.end());
                printTestResult("Iterator range overflow test", false);
            } catch(const std::exception& e) {
                printTestResult("Iterator range overflow throws", true);
                std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            }
        }
    }

    // 5. Object Behavior Tests
    {
        printHeader("Object Behavior Tests");

        // Copy constructor
        {
            Span original(5);
            original.addNumber(1);
            original.addNumber(2);

            Span copy(original);
            try {
                printTestResult("Copy constructor - Same spans",
                    copy.shortestSpan() == original.shortestSpan() &&
                    copy.longestSpan() == original.longestSpan());

                // Modify copy
                copy.addNumber(3);
                printTestResult("Copy constructor - Independent objects", true);
            } catch(const std::exception& e) {
                printTestResult("Copy constructor test", false);
                std::cout << RED << "Error: " << e.what() << RESET << std::endl;
            }
        }

        // Assignment operator
        {
            Span sp1(5);
            sp1.addNumber(1);
            sp1.addNumber(2);

            Span sp2(10);  // Different size
            sp2 = sp1;

            try {
                printTestResult("Assignment operator - Same spans",
                    sp2.shortestSpan() == sp1.shortestSpan() &&
                    sp2.longestSpan() == sp1.longestSpan());
            } catch(const std::exception& e) {
                printTestResult("Assignment operator test", false);
                std::cout << RED << "Error: " << e.what() << RESET << std::endl;
            }
        }
    }

    // 6. Iterator Range Tests
    {
        printHeader("Iterator Range Tests");

        // Vector iterator test
        {
            std::vector<int> vec;
            for(int i = 0; i < 5; ++i)
                vec.push_back(i * 2);  // 0,2,4,6,8

            Span sp(5);
            try {
                sp.addNumber(vec.begin(), vec.end());
                printTestResult("Vector iterator addition", true);
                printTestResult("Vector iterator - shortest span", sp.shortestSpan() == 2);
                printTestResult("Vector iterator - longest span", sp.longestSpan() == 8);
            } catch(const std::exception& e) {
                printTestResult("Vector iterator test", false);
                std::cout << RED << "Error: " << e.what() << RESET << std::endl;
            }
        }

        // List iterator test
        {
            std::list<int> lst;
            for(int i = 0; i < 3; ++i)
                lst.push_back(i + 1);  // 1,2,3

            Span sp(3);
            try {
                sp.addNumber(lst.begin(), lst.end());
                printTestResult("List iterator addition", true);
                printTestResult("List iterator - shortest span", sp.shortestSpan() == 1);
                printTestResult("List iterator - longest span", sp.longestSpan() == 2);
            } catch(const std::exception& e) {
                printTestResult("List iterator test", false);
                std::cout << RED << "Error: " << e.what() << RESET << std::endl;
            }
        }
    }

    return 0;
}