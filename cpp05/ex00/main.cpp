#include "Bureaucrat.hpp"

// Color definitions
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
    // Subject PDF Tests
    {
        printHeader("Subject PDF Test");
        try {
            Bureaucrat high("High Grade", 1);
            Bureaucrat low("Low Grade", 150);

            std::cout << high;
            std::cout << low;

            printTestResult("Create valid bureaucrats", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Create valid bureaucrats", false);
        }
    }

    // Basic Functionality Tests
    {
        printHeader("Basic Operations - Constructors");

        // Test middle grade (75)
        try {
            Bureaucrat middleGrade("Kevin", 75);
            printTestResult("Middle grade construction (75)", true);
            std::cout << CYAN << "Created: " << RESET << middleGrade;
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Middle grade construction (75)", false);
        }

        // Test extreme invalid grade
        try {
            Bureaucrat extremeGrade("Bob", -5);
            printTestResult("Extreme invalid grade check (-5)", false);
        } catch (Bureaucrat::GradeTooHighException& e) {
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            printTestResult("Extreme invalid grade check (-5)", true);
        }

        // Test Constructors
        try {
            Bureaucrat defaultBureaucrat;
            printTestResult("Default constructor", defaultBureaucrat.getGrade() == 150);

            Bureaucrat namedBureaucrat("Bob", 75);
            bool constructorTest = (namedBureaucrat.getName() == "Bob" && namedBureaucrat.getGrade() == 75);
            printTestResult("Parameterized constructor", constructorTest);

            Bureaucrat copyBureaucrat(namedBureaucrat);
            bool copyTest = (copyBureaucrat.getName() == namedBureaucrat.getName() &&
                           copyBureaucrat.getGrade() == namedBureaucrat.getGrade());
            printTestResult("Copy constructor", copyTest);

            Bureaucrat assignBureaucrat;
            assignBureaucrat = namedBureaucrat;
            bool assignTest = (assignBureaucrat.getGrade() == namedBureaucrat.getGrade());
            printTestResult("Assignment operator", assignTest);

        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception in constructor tests: " << e.what() << RESET << std::endl;
        }
    }

    // Edge Cases
    {
        printHeader("Edge Cases");

        // Test Grade Too High
        try {
            Bureaucrat tooHigh("Too High", 0);
            printTestResult("Grade too high check", false);
        } catch (Bureaucrat::GradeTooHighException& e) {
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            printTestResult("Grade too high check", true);
        }

        // Test Grade Too Low
        try {
            Bureaucrat tooLow("Too Low", 151);
            printTestResult("Grade too low check", false);
        } catch (Bureaucrat::GradeTooLowException& e) {
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            printTestResult("Grade too low check", true);
        }
    }

    // Grade Modification Tests
    {
        printHeader("Grade Modification");

        // Test middle grade increment
        try {
            Bureaucrat b("Middle", 75);
            std::cout << CYAN << "Before increment: " << RESET << b;
            b.incrementGrade();
            bool success = b.getGrade() == 74;
            std::cout << CYAN << "After increment: " << RESET << b;
            printTestResult("Increment middle grade (75 -> 74)", success);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Increment middle grade", false);
        }

        // Test middle grade decrement
        try {
            Bureaucrat b("Middle", 75);
            std::cout << CYAN << "Before decrement: " << RESET << b;
            b.decrementGrade();
            bool success = b.getGrade() == 76;
            std::cout << CYAN << "After decrement: " << RESET << b;
            printTestResult("Decrement middle grade (75 -> 76)", success);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Decrement middle grade", false);
        }

        // Test increment
        try {
            Bureaucrat b("Test", 2);
            b.incrementGrade();
            printTestResult("Increment grade", b.getGrade() == 1);

            try {
                b.incrementGrade();
                printTestResult("Prevent increment above 1", false);
            } catch (Bureaucrat::GradeTooHighException& e) {
                std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
                printTestResult("Prevent increment above 1", true);
            }
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception in increment tests: " << e.what() << RESET << std::endl;
        }

        // Test decrement
        try {
            Bureaucrat b("Test", 149);
            b.decrementGrade();
            printTestResult("Decrement grade", b.getGrade() == 150);

            try {
                b.decrementGrade();
                printTestResult("Prevent decrement below 150", false);
            } catch (Bureaucrat::GradeTooLowException& e) {
                std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
                printTestResult("Prevent decrement below 150", true);
            }
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception in decrement tests: " << e.what() << RESET << std::endl;
        }
    }

    // Output Operator Test
    {
        printHeader("Output Operator");

        Bureaucrat b("OutputTest", 42);
        std::cout << CYAN << "Testing output operator (visual check):" << RESET << std::endl;
        std::cout << b;

        // Can't automatically verify output format, requires visual inspection
        std::cout << "Above output should be: 'OutputTest, bureaucrat grade 42'" << std::endl;
    }

    return 0;
}