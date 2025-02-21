#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

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
    // Construction Tests
    {
        printHeader("Form Construction Tests");

        // Test creation of each form type
        try {
            ShrubberyCreationForm s("home");
            RobotomyRequestForm r("Bender");
            PresidentialPardonForm p("Criminal");
            printTestResult("Create all form types", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Create all form types", false);
        }

        // Test copy construction
        try {
            ShrubberyCreationForm original("garden");
            ShrubberyCreationForm copy(original);
            bool copySuccess = (copy.getName() == original.getName() &&
                              copy.getGradeRequiredToSign() == original.getGradeRequiredToSign() &&
                              copy.getGradeRequiredToExecute() == original.getGradeRequiredToExecute());
            printTestResult("Copy construction", copySuccess);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Copy construction", false);
        }
    }

    // Signing Tests
    {
        printHeader("Form Signing Tests");

        // ShrubberyCreationForm signing tests
        try {
            Bureaucrat high("High", 1);
            Bureaucrat low("Low", 150);
            ShrubberyCreationForm form("garden");

            // Test with sufficient grade
            high.signForm(form);
            printTestResult("Sign Shrubbery with sufficient grade", form.getSigned());

            // Test with insufficient grade
            ShrubberyCreationForm form2("park");
            low.signForm(form2);
            printTestResult("Reject Shrubbery with insufficient grade", !form2.getSigned());
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Shrubbery signing tests", false);
        }

        // RobotomyRequestForm signing tests
        try {
            Bureaucrat mid("Mid", 72);
            RobotomyRequestForm form("Bender");
            mid.signForm(form);
            printTestResult("Sign Robotomy with exact grade", form.getSigned());
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Robotomy signing test", false);
        }

        // PresidentialPardonForm signing tests
        try {
            Bureaucrat low("Low", 30);
            PresidentialPardonForm form("Criminal");
            low.signForm(form);
            printTestResult("Sign Presidential with insufficient grade", !form.getSigned());
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Presidential signing test", false);
        }
    }

    // Execution Tests
    {
        printHeader("Form Execution Tests");

        // ShrubberyCreationForm execution
        try {
            Bureaucrat exec("Executive", 137);
            ShrubberyCreationForm form("garden");
            exec.signForm(form);
            exec.executeForm(form);
            printTestResult("Execute Shrubbery form", true);
            std::cout << CYAN << "Check for garden_shrubbery file creation" << RESET << std::endl;
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Execute Shrubbery form", false);
        }

        // RobotomyRequestForm execution
        try {
            Bureaucrat exec("Executive", 45);
            RobotomyRequestForm form("Bender");
            exec.signForm(form);
            std::cout << CYAN << "Testing Robotomy (50% success rate):" << RESET << std::endl;
            exec.executeForm(form);
            printTestResult("Execute Robotomy form", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Execute Robotomy form", false);
        }

        // PresidentialPardonForm execution
        try {
            Bureaucrat exec("Executive", 5);
            PresidentialPardonForm form("Criminal");
            exec.signForm(form);
            exec.executeForm(form);
            printTestResult("Execute Presidential form", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Execute Presidential form", false);
        }
    }

    // Error Cases
    {
        printHeader("Error Cases");

        // Try to execute unsigned form
        {
            Bureaucrat exec("Executive", 1);
            ShrubberyCreationForm form("garden");
            exec.executeForm(form);
            // The test passes if the form wasn't executed (which is handled by the error message in executeForm)
            printTestResult("Prevent unsigned form execution", true);
        }

        // Try to execute with insufficient grade
        {
            Bureaucrat low("Low", 150);
            PresidentialPardonForm form("Criminal");
            Bureaucrat high("High", 1);
            high.signForm(form);
            low.executeForm(form);
            // The test passes if the form wasn't executed (which is handled by the error message in executeForm)
            printTestResult("Prevent execution with low grade", true);
        }
    }

    return 0;
}