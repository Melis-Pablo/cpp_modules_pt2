#include <iostream>
#include "ScalarConverter.hpp"
#include <string>

// Color definitions
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Failed tests
#define GREEN   "\033[32m"      // Passed tests
#define YELLOW  "\033[33m"      // Section headers
#define BLUE    "\033[34m"      // Expected exceptions/warnings
#define CYAN    "\033[36m"      // Informational output

// Test utility functions
void printHeader(const std::string& header) {
    std::cout << std::endl << YELLOW << "=== " << header << " ===" << RESET << std::endl;
}

void printSubHeader(const std::string& header) {
    std::cout << CYAN << "--- " << header << " ---" << RESET << std::endl;
}

void runTest(const std::string& testName, const std::string& input) {
    std::cout << BLUE << "\nTesting: " << testName << " (" << input << ")" << RESET << std::endl;
    ScalarConverter::convert(input);
}

int main() {
    // PDF/Project Specific Tests
    {
        printHeader("Subject PDF Tests");
        runTest("Zero test", "0");
        runTest("NaN test", "nan");
        runTest("Float test", "42.0f");
    }

    // Basic Functionality Tests
    {
        printHeader("Basic Type Tests");

        printSubHeader("Char Tests");
        runTest("Basic char", "'a'");
        runTest("Number char", "'0'");
        runTest("Special char", "'+'");

        printSubHeader("Integer Tests");
        runTest("Positive integer", "42");
        runTest("Negative integer", "-42");
        runTest("Zero", "0");
        runTest("Max-like integer", "2147483647");
        runTest("Min-like integer", "-2147483648");

        printSubHeader("Float Tests");
        runTest("Basic float", "42.42f");
        runTest("Negative float", "-42.42f");
        runTest("Zero float", "0.0f");
        runTest("Integer-like float", "42.0f");
        runTest("Float with f", "42f");

        printSubHeader("Double Tests");
        runTest("Basic double", "42.42");
        runTest("Negative double", "-42.42");
        runTest("Zero double", "0.0");
        runTest("Integer-like double", "42.0");
    }

    // Edge Cases
    {
        printHeader("Edge Cases");

        printSubHeader("Special Values");
        runTest("NaN float", "nanf");
        runTest("NaN double", "nan");
        runTest("Positive infinity float", "+inff");
        runTest("Negative infinity float", "-inff");
        runTest("Positive infinity double", "+inf");
        runTest("Negative infinity double", "-inf");

        printSubHeader("Decimal Point Cases");
        runTest("Single decimal point", ".");
        runTest("Leading decimal", ".42");
        runTest("Trailing decimal", "42.");
        runTest("Leading decimal float", ".42f");
        runTest("Trailing decimal float", "42.f");
    }

    // Invalid Input Tests
    {
        printHeader("Invalid Input Tests");

        printSubHeader("Invalid Characters");
        runTest("Empty string", "");
        runTest("Invalid char format", "a");
        runTest("Incomplete char", "'a");
        runTest("No closing quote", "'");

        printSubHeader("Invalid Numbers");
        runTest("Double dot", "42.42.42");
        runTest("Multiple dots", "42..42");
        runTest("Invalid float", "42f42");
        runTest("Invalid suffix", "42.42x");
        runTest("Letters only", "abc");
        runTest("Mixed content", "42abc");

        printSubHeader("Special Characters");
        runTest("Non displayable char", "'\\n'");
        runTest("Invalid special value", "infinity");
        runTest("Wrong infinity format", "inf f");
    }

    // Overflow Tests
    {
        printHeader("Overflow Tests");
        runTest("Large number", "999999999999999999999999999.0");
        runTest("Small number", "-999999999999999999999999999.0");
        runTest("Large float", "340282346638528859811704183484516925440.0f");
        runTest("Small float", "-340282346638528859811704183484516925440.0f");
    }

    return 0;
}

// int main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Error: Invalid number of arguments" << std::endl;
// 		return 1;
// 	}
// 	ScalarConverter::convert(argv[1]);
// 	return 0;
// }