#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <unistd.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

void testShrubberyForm() {
    std::cout << BOLD << BLUE << "\n=== Shrubbery Creation Form Tests ===" << RESET << std::endl;

    try {
        // Test valid execution
        std::cout << CYAN << "\nTesting valid execution..." << RESET << std::endl;
        Bureaucrat b1("Bob", 137);  // Exactly enough to execute
        ShrubberyCreationForm f1("garden");
        std::cout << f1 << std::endl;
        b1.signForm(f1);
        b1.executeForm(f1);

        // Test unsigned execution
        std::cout << CYAN << "\nTesting unsigned form execution..." << RESET << std::endl;
        ShrubberyCreationForm f2("park");
        Bureaucrat b2("Alice", 137);
        b2.executeForm(f2);

        // Test too low grade
        std::cout << CYAN << "\nTesting too low grade..." << RESET << std::endl;
        Bureaucrat b3("Charlie", 150);
        ShrubberyCreationForm f3("yard");
        b1.signForm(f3);  // Have Bob sign it
        b3.executeForm(f3);  // Charlie tries to execute

    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

void testRobotomyForm() {
    std::cout << BOLD << BLUE << "\n=== Robotomy Request Form Tests ===" << RESET << std::endl;

    try {
        // Test multiple executions to see randomness
        std::cout << CYAN << "\nTesting multiple robotomy attempts..." << RESET << std::endl;
        Bureaucrat b1("Dave", 45);
        RobotomyRequestForm f1("Bender");
        b1.signForm(f1);
        for (int i = 0; i < 5; i++) {
            std::cout << YELLOW << "\nAttempt " << i + 1 << ":" << RESET << std::endl;
            b1.executeForm(f1);
            sleep(1);
        }

        // Test grade requirements
        std::cout << CYAN << "\nTesting grade requirements..." << RESET << std::endl;
        Bureaucrat b2("Eve", 73);  // Can sign but not execute
        RobotomyRequestForm f2("Wall-E");
        b2.signForm(f2);
        b2.executeForm(f2);

    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

void testPresidentialForm() {
    std::cout << BOLD << BLUE << "\n=== Presidential Pardon Form Tests ===" << RESET << std::endl;

    try {
        // Test successful pardon
        std::cout << CYAN << "\nTesting successful pardon..." << RESET << std::endl;
        Bureaucrat president("President", 5);
        PresidentialPardonForm f1("Arthur Dent");
        president.signForm(f1);
        president.executeForm(f1);

        // Test high enough to sign but not execute
        std::cout << CYAN << "\nTesting sign-only permissions..." << RESET << std::endl;
        Bureaucrat vp("Vice President", 24);
        PresidentialPardonForm f2("Zaphod");
        vp.signForm(f2);
        vp.executeForm(f2);

        // Test too low for both
        std::cout << CYAN << "\nTesting insufficient permissions..." << RESET << std::endl;
        Bureaucrat intern("Intern", 150);
        PresidentialPardonForm f3("Trillian");
        intern.signForm(f3);
        intern.executeForm(f3);

    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }
}

int main() {
    testShrubberyForm();
    testRobotomyForm();
    testPresidentialForm();

    std::cout << BOLD << BLUE << "\n=== Cross-Form Tests ===" << RESET << std::endl;

    try {
        // Test one bureaucrat with multiple forms
        Bureaucrat boss("Boss", 1);
        ShrubberyCreationForm s("garden2");
        RobotomyRequestForm r("candidate");
        PresidentialPardonForm p("criminal");

        std::cout << CYAN << "\nTesting high-level bureaucrat with all forms..." << RESET << std::endl;
        boss.signForm(s);
        boss.signForm(r);
        boss.signForm(p);
        boss.executeForm(s);
        boss.executeForm(r);
        boss.executeForm(p);

    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    return 0;
}