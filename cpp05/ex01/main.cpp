#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

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
    // Form Construction Tests
    {
        printHeader("Additional Form Construction Tests");

        // Test: Create form with exec grade too high
        try {
            Form f("Exec Too High", 75, 0);
            printTestResult("Create form with exec grade too high", false);
        } catch (Form::GradeTooHighException& e) {
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            printTestResult("Create form with exec grade too high", true);
        }

        // Test: Create form with sign grade too low
        try {
            Form f("Sign Too Low", 151, 75);
            printTestResult("Create form with sign grade too low", false);
        } catch (Form::GradeTooLowException& e) {
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            printTestResult("Create form with sign grade too low", true);
        }
    }

    // Form Construction Tests
    {
        printHeader("Form Construction Tests");

        // Valid form creation (middle-range grades)
        try {
            Form f1("Basic Form", 75, 75);
            printTestResult("Create form with valid grades", true);
            std::cout << CYAN << "Form created: " << std::endl << f1 << RESET << std::endl;
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Create form with valid grades", false);
        }

        // Invalid sign grade (too high)
        try {
            Form f2("Invalid Form", 0, 75);
            printTestResult("Create form with too high sign grade", false);
        } catch (Form::GradeTooHighException& e) {
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            printTestResult("Create form with too high sign grade", true);
        }

        // Invalid execute grade (too low)
        try {
            Form f3("Invalid Form", 75, 151);
            printTestResult("Create form with too low execute grade", false);
        } catch (Form::GradeTooLowException& e) {
            std::cout << BLUE << "Expected error: " << e.what() << RESET << std::endl;
            printTestResult("Create form with too low execute grade", true);
        }
    }

    // Form Copy and Assignment Tests
    {
        // Test: Copy unsigned form
        Form unsignedOriginal("Unsigned Original", 75, 75);
        Form unsignedCopy(unsignedOriginal);
        bool unsignedCopyTest = (!unsignedCopy.getSigned() &&
                                unsignedCopy.getName() == unsignedOriginal.getName() &&
                                unsignedCopy.getGradeRequiredToSign() == unsignedOriginal.getGradeRequiredToSign());
        printTestResult("Copy unsigned form", unsignedCopyTest);

        // Test: Assignment operator with signed form
        Form signedOriginal("Signed Original", 75, 75);
        Bureaucrat highGrade("High Grade", 1);
        try {
            highGrade.signForm(signedOriginal);
            Form assignedForm("Different", 100, 100);
            assignedForm = signedOriginal;
            bool signedAssignTest = (assignedForm.getSigned() == signedOriginal.getSigned() &&
                                   assignedForm.getName() == "Different"); // Name shouldn't change
            printTestResult("Assignment operator with signed form", signedAssignTest);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Assignment operator with signed form", false);
        }
    }

    // Form Copy and Assignment Tests
    {
        printHeader("Form Copy and Assignment Tests");

        Form original("Original", 50, 50);
        Form copy(original);

        bool copyTest = (original.getName() == copy.getName() &&
                        original.getGradeRequiredToSign() == copy.getGradeRequiredToSign() &&
                        original.getGradeRequiredToExecute() == copy.getGradeRequiredToExecute() &&
                        original.getSigned() == copy.getSigned());

        printTestResult("Copy constructor test", copyTest);

        Form assigned("Different", 75, 75);
        assigned = original;

        bool assignTest = (assigned.getSigned() == original.getSigned() &&
                          assigned.getName() == "Different"); // Name shouldn't change

        printTestResult("Assignment operator test", assignTest);
    }

    // Form Signing Tests
    {
        // Test: Valid signing (bureaucrat grade > required)
        try {
            Bureaucrat b("Better Grade", 25);
            Form f("Easy Form", 50, 50);
            b.signForm(f);
            printTestResult("Sign form with better than required grade", f.getSigned());
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Sign form with better than required grade", false);
        }

        // Test: Valid signing (bureaucrat grade = required)
        try {
            Bureaucrat b("Equal Grade", 75);
            Form f("Equal Form", 75, 75);
            b.signForm(f);
            printTestResult("Sign form with exactly required grade", f.getSigned());
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Sign form with exactly required grade", false);
        }

        // Test: Highest grade bureaucrat with lowest grade form
        try {
            Bureaucrat b("Highest", 1);
            Form f("Lowest Requirements", 150, 150);
            b.signForm(f);
            printTestResult("Highest grade bureaucrat with lowest grade form", f.getSigned());
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Highest grade bureaucrat with lowest grade form", false);
        }

        // Test: Lowest grade bureaucrat with highest grade form
        try {
            Bureaucrat b("Lowest", 150);
            Form f("Highest Requirements", 1, 1);
            b.signForm(f);
            printTestResult("Lowest grade bureaucrat with highest grade form", !f.getSigned());
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Lowest grade bureaucrat with highest grade form", false);
        }
    }

    // Form Signing Tests
    {
        printHeader("Form Signing Tests");

        // Successful signing (high grade bureaucrat, low requirement form)
        try {
            Bureaucrat highGrade("High Grade", 1);  // Highest possible grade
            Form easyForm("Easy Form", 50, 50);     // Lower grade requirement

            std::cout << CYAN << "Before signing attempt:" << std::endl;
            std::cout << easyForm << RESET << std::endl;

            highGrade.signForm(easyForm);
            printTestResult("Sign form with sufficient grade", easyForm.getSigned());

            std::cout << CYAN << "After signing attempt:" << std::endl;
            std::cout << easyForm << RESET << std::endl;
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Sign form with sufficient grade", false);
        }

        // Failed signing due to low grade
        try {
            Bureaucrat lowGrade("Low Grade", 150);  // Lowest possible grade
            Form hardForm("Hard Form", 1, 1);       // Highest grade requirement

            std::cout << CYAN << "Attempting to sign with insufficient grade:" << std::endl;
            lowGrade.signForm(hardForm);
            printTestResult("Proper handling of insufficient grade", !hardForm.getSigned());
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception handling: " << e.what() << RESET << std::endl;
            printTestResult("Proper handling of insufficient grade", false);
        }

        // Already signed form
        try {
            Bureaucrat highGrade("High Grade", 1);
            Form form("Test Form", 50, 50);

            highGrade.signForm(form);
            std::cout << CYAN << "Attempting to sign already signed form:" << std::endl;
            highGrade.signForm(form);
            printTestResult("Handle already signed form", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception handling: " << e.what() << RESET << std::endl;
            printTestResult("Handle already signed form", false);
        }
    }

    // Output Format Tests
    {
        printHeader("Output Format Tests");

        Form f1("Test Form", 75, 100);
        std::cout << CYAN << "Testing form output format:" << RESET << std::endl;
        std::cout << f1 << std::endl;

        // Visual verification required
        std::cout << "Please verify the above output contains:" << std::endl;
        std::cout << "- Form name" << std::endl;
        std::cout << "- Signed status" << std::endl;
        std::cout << "- Required grades for signing and execution" << std::endl;
    }

    // Edge Cases
    {
        printHeader("Edge Cases");

        // Highest grade requirements
        try {
            Form highestForm("Highest Grade Form", 1, 1);  // Requires highest possible grade
            printTestResult("Create form with highest grade requirements", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Create form with highest grade requirements", false);
        }

        // Lowest grade requirements
        try {
            Form lowestForm("Lowest Grade Form", 150, 150);  // Requires lowest possible grade
            printTestResult("Create form with lowest grade requirements", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Create form with lowest grade requirements", false);
        }

        // Mixed grade requirements
        try {
            Form mixedForm("Mixed Grade Form", 1, 150);  // Highest sign, lowest execute
            printTestResult("Create form with mixed grade requirements", true);
        } catch (std::exception& e) {
            std::cout << RED << "Unexpected exception: " << e.what() << RESET << std::endl;
            printTestResult("Create form with mixed grade requirements", false);
        }
    }
    return 0;
}