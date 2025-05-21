#include "PmergeMe.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cstring> // For strcpy
#include <algorithm>

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

// Helper function to generate random sequence
std::vector<int> generateRandomSequence(int size, int maxValue = 10000) {
    std::vector<int> sequence;
    for (int i = 0; i < size; i++) {
        sequence.push_back(rand() % maxValue);
    }
    return sequence;
}

// Helper function to check if a sequence is sorted
bool isSorted(const std::vector<int>& sequence) {
    for (size_t i = 1; i < sequence.size(); i++) {
        if (sequence[i] < sequence[i - 1]) {
            return false;
        }
    }
    return true;
}

// Helper function to convert argc/argv style to proper test
void testWithArguments(const std::vector<int>& args) {
    PmergeMe pmerge;

    // Convert vector to argc/argv style
    std::vector<std::string> argStrings;
    argStrings.push_back("program"); // Program name

    for (size_t i = 0; i < args.size(); i++) {
                    std::stringstream ss;
            ss << args[i];
            argStrings.push_back(ss.str());
    }

    // Create argc/argv
    int argc = argStrings.size();
    char** argv = new char*[argc];

    for (int i = 0; i < argc; i++) {
        argv[i] = new char[argStrings[i].length() + 1];
        strcpy(argv[i], argStrings[i].c_str());
    }

    // Run test
    try {
        pmerge.processInput(argc, argv);
        pmerge.sortAndMeasure();
    } catch (const std::exception& e) {
        std::cout << BLUE << "Exception: " << e.what() << RESET << std::endl;
    }

    // Clean up
    for (int i = 0; i < argc; i++) {
        delete[] argv[i];
    }
    delete[] argv;
}

int main(int ac, char **av) {
    srand(time(NULL)); // Seed random number generator
    // Edge Cases
    {
        printHeader("Large Sequence");

        // Test with 3000 random integers
        if (ac != 2)
            return 0;
        std::cout << CYAN << "Testing with " << std::atoi(av[1]) << " random integers..." << RESET << std::endl;
        std::vector<int> largeSequence = generateRandomSequence((std::atoi(av[0])));

        PmergeMe pmerge;

        // Convert vector to argc/argv style
        std::vector<std::string> argStrings;
        argStrings.push_back("program"); // Program name

        for (size_t i = 0; i < largeSequence.size(); i++) {
            std::stringstream ss;
            ss << largeSequence[i];
            argStrings.push_back(ss.str());
        }

        // Create argc/argv
        int argc = argStrings.size();
        char** argv = new char*[argc];

        for (int i = 0; i < argc; i++) {
            argv[i] = new char[argStrings[i].length() + 1];
            strcpy(argv[i], argStrings[i].c_str());
        }

        // Process and sort
        try {
            pmerge.processInput(argc, argv);
            pmerge.sortAndMeasure();

            // Clean up
            for (int i = 0; i < argc; i++) {
                delete[] argv[i];
            }
            delete[] argv;

        } catch (const std::exception& e) {
            std::cout << BLUE << "Exception: " << e.what() << RESET << std::endl;

            // Clean up
            for (int i = 0; i < argc; i++) {
                delete[] argv[i];
            }
            delete[] argv;
        }
    }
    // // Exception Handling
    // {
    //     printHeader("Exception Handling");

    //     // Test with negative number
    //     std::cout << CYAN << "Testing with negative number..." << RESET << std::endl;
    //     std::vector<int> negativeTest;
    //     negativeTest.push_back(1);
    //     negativeTest.push_back(2);
    //     negativeTest.push_back(-3);
    //     negativeTest.push_back(4);

    //     PmergeMe pmerge1;

    //     // Convert vector to argc/argv style
    //     std::vector<std::string> argStrings1;
    //     argStrings1.push_back("program"); // Program name

    //     for (size_t i = 0; i < negativeTest.size(); i++) {
    //                         std::stringstream ss;
    //             ss << negativeTest[i];
    //             argStrings1.push_back(ss.str());
    //     }

    //     // Create argc/argv
    //     int argc1 = argStrings1.size();
    //     char** argv1 = new char*[argc1];

    //     for (int i = 0; i < argc1; i++) {
    //         argv1[i] = new char[argStrings1[i].length() + 1];
    //         strcpy(argv1[i], argStrings1[i].c_str());
    //     }

    //     // Process and sort
    //     try {
    //         pmerge1.processInput(argc1, argv1);
    //         pmerge1.sortAndMeasure();
    //         printTestResult("Negative Number Test", false);
    //     } catch (const std::exception& e) {
    //         std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
    //         printTestResult("Negative Number Test", true);
    //     }

    //     // Clean up
    //     for (int i = 0; i < argc1; i++) {
    //         delete[] argv1[i];
    //     }
    //     delete[] argv1;

    //     // Test with non-numeric input
    //     std::cout << CYAN << "Testing with non-numeric input..." << RESET << std::endl;

    //     const char* argv2[] = {"program", "1", "2", "abc", "4"};
    //     PmergeMe pmerge2;

    //     try {
    //         pmerge2.processInput(5, (char**)argv2);
    //         pmerge2.sortAndMeasure();
    //         printTestResult("Non-Numeric Input Test", false);
    //     } catch (const std::exception& e) {
    //         std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
    //         printTestResult("Non-Numeric Input Test", true);
    //     }
    // }
    return 0;
}