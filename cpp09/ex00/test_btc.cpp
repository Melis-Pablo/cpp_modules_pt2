#include "BitcoinExchange.hpp"
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

int main(int argc, char **argv) {
    // PDF/Project Specific Tests
    {
        printHeader("Subject PDF Test");

        if (argc != 2) {
            std::cout << "Usage: " << argv[0] << " [input_file]" << std::endl;
            std::cout << "Running default test with 'input.txt'" << std::endl;

            try {
                BitcoinExchange exchange;
                exchange.processInputFile("input.txt");
                printTestResult("Process Input File", true);
            } catch (const std::exception& e) {
                std::cout << BLUE << "Exception: " << e.what() << RESET << std::endl;
                printTestResult("Process Input File", false);
            }
        } else {
            try {
                BitcoinExchange exchange;
                exchange.processInputFile(argv[1]);
                printTestResult("Process Input File", true);
            } catch (const std::exception& e) {
                std::cout << BLUE << "Exception: " << e.what() << RESET << std::endl;
                printTestResult("Process Input File", false);
            }
        }
    }

    // Basic Functionality Tests
    {
        printHeader("Basic Operations");

        try {
            BitcoinExchange exchange;
            printTestResult("Default Constructor", true);

            // Test database loading
            float rate = exchange.getExchangeRate("2021-01-02");
            std::cout << CYAN << "Exchange rate for 2021-01-02: " << rate << RESET << std::endl;
            printTestResult("Database Loading", rate > 0);

            // Test value calculation
            float value = 10.0;
            float result = value * rate;
            std::cout << CYAN << "10 BTC on 2021-01-02 = " << result << RESET << std::endl;
            printTestResult("Value Calculation", true);
        } catch (const std::exception& e) {
            std::cout << BLUE << "Exception: " << e.what() << RESET << std::endl;
            printTestResult("Basic Operations", false);
        }
    }

    // Edge Cases
    {
        printHeader("Edge Cases");

        try {
            BitcoinExchange exchange;

            // Test date before database start
            float rate = exchange.getExchangeRate("2000-01-01");
            std::cout << CYAN << "Exchange rate for 2000-01-01: " << rate << RESET << std::endl;
            printTestResult("Date Before Database", rate == 0);

            // Test date after database end
            rate = exchange.getExchangeRate("2023-01-01");
            std::cout << CYAN << "Exchange rate for 2023-01-01: " << rate << RESET << std::endl;
            printTestResult("Date After Database", rate > 0);

            // Test date with no exact match
            rate = exchange.getExchangeRate("2021-01-03");
            std::cout << CYAN << "Exchange rate for 2021-01-03: " << rate << RESET << std::endl;
            printTestResult("Date Without Exact Match", rate > 0);
        } catch (const std::exception& e) {
            std::cout << BLUE << "Exception: " << e.what() << RESET << std::endl;
            printTestResult("Edge Cases", false);
        }
    }

    // Exception Handling
    {
        printHeader("Exception Handling");

        // Test non-existent file
        try {
            BitcoinExchange exchange;
            exchange.processInputFile("non_existent_file.txt");
            printTestResult("Non-existent File", false);
        } catch (const std::exception& e) {
            std::cout << BLUE << "Expected exception: " << e.what() << RESET << std::endl;
            printTestResult("Non-existent File", true);
        }

        // Test date validation
        BitcoinExchange exchange;
        bool valid;

        valid = exchange.isValidDate("2021-01-02");
        printTestResult("Valid Date", valid);

        valid = exchange.isValidDate("2021-13-02"); // Invalid month
        printTestResult("Invalid Month", !valid);

        valid = exchange.isValidDate("2021-02-30"); // Invalid day
        printTestResult("Invalid Day", !valid);

        valid = exchange.isValidDate("202-01-02");  // Invalid format
        printTestResult("Invalid Format", !valid);
    }

    // Object Behavior Tests
    {
        printHeader("Object Behavior");

        // Test copy constructor
        try {
            BitcoinExchange exchange1;
            float rate1 = exchange1.getExchangeRate("2021-01-02");

            BitcoinExchange exchange2(exchange1);
            float rate2 = exchange2.getExchangeRate("2021-01-02");

            printTestResult("Copy Constructor", rate1 == rate2);

            // Test assignment operator
            BitcoinExchange exchange3;
            exchange3 = exchange1;
            float rate3 = exchange3.getExchangeRate("2021-01-02");

            printTestResult("Assignment Operator", rate1 == rate3);
        } catch (const std::exception& e) {
            std::cout << BLUE << "Exception: " << e.what() << RESET << std::endl;
            printTestResult("Object Behavior", false);
        }
    }

    return 0;
}