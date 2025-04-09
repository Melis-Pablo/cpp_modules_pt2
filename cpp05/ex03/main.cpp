#include <iostream>
#include "Intern.hpp"
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
    // Canonical Form Tests
    {
        printHeader("Canonical Form Tests");

        try {
            // Default constructor
            Intern intern1;

            // Copy constructor
            Intern intern2(intern1);

            // Assignment operator
            Intern intern3;
            intern3 = intern1;

            printTestResult("Canonical form implementation", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Canonical form implementation", false);
        }
    }

    // Form Creation Tests
    {
        printHeader("Form Creation Tests");

        Intern intern;
        Bureaucrat bureaucrat("Tester", 1);  // Highest grade to sign/execute all forms

        // Presidential Pardon Form
        try {
            AForm* form = intern.makeForm("presidential pardon", "Target1");
            bool success = (form != NULL &&
                          dynamic_cast<PresidentialPardonForm*>(form) != NULL);
            printTestResult("Create Presidential Pardon Form", success);

            // Test the created form
            if (form) {
                bureaucrat.signForm(*form);
                bureaucrat.executeForm(*form);
                delete form;
            }
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Create Presidential Pardon Form", false);
        }

        // Robotomy Request Form
        try {
            AForm* form = intern.makeForm("robotomy request", "Target2");
            bool success = (form != NULL &&
                          dynamic_cast<RobotomyRequestForm*>(form) != NULL);
            printTestResult("Create Robotomy Request Form", success);

            // Test the created form
            if (form) {
                bureaucrat.signForm(*form);
                bureaucrat.executeForm(*form);
                delete form;
            }
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Create Robotomy Request Form", false);
        }

        // Shrubbery Creation Form
        try {
            AForm* form = intern.makeForm("shrubbery creation", "Target3");
            bool success = (form != NULL &&
                          dynamic_cast<ShrubberyCreationForm*>(form) != NULL);
            printTestResult("Create Shrubbery Creation Form", success);

            // Test the created form
            if (form) {
                bureaucrat.signForm(*form);
                bureaucrat.executeForm(*form);
                delete form;
            }
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Create Shrubbery Creation Form", false);
        }
    }

    // Error Cases
    {
        printHeader("Error Cases");

        Intern intern;

        // Test with invalid form name
        try {
            AForm* form = intern.makeForm("invalid form", "Target");
            if (form) {
                delete form;
            }
            printTestResult("Handle invalid form name", false);
        } catch (Intern::FormNotFoundException& e) {
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            printTestResult("Handle invalid form name", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception type: " << e.what() << RESET << std::endl;
            printTestResult("Handle invalid form name", false);
        }

        // Test with case sensitivity
        try {
            AForm* form = intern.makeForm("PRESIDENTIAL PARDON", "Target");
            if (form) {
                delete form;
            }
            printTestResult("Handle case sensitive form name", false);
        } catch (Intern::FormNotFoundException& e) {
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            printTestResult("Handle case sensitive form name", true);
        }
    }

    // Multiple Interns Test
    {
        printHeader("Multiple Interns Test");

        try {
            Intern intern1;
            Intern intern2;

            AForm* form1 = intern1.makeForm("robotomy request", "Target1");
            AForm* form2 = intern2.makeForm("presidential pardon", "Target2");

            bool success = (form1 != NULL && form2 != NULL);
            printTestResult("Multiple interns creating forms", success);

            delete form1;
            delete form2;
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Multiple interns creating forms", false);
        }
    }

    return 0;
}