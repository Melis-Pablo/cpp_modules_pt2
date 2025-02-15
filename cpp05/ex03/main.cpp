#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

int main()
{
    std::cout << BOLD << BLUE << "\n=== Intern Form Creation Tests ===" << RESET << std::endl;

    // Test 1: Create an Intern
    std::cout << CYAN << "\nCreating Intern..." << RESET << std::endl;
    Intern intern;

    // Test 2: Create Presidential Pardon Form
    std::cout << CYAN << "\nTesting Presidential Pardon Form creation..." << RESET << std::endl;
    try {
        AForm* form = intern.makeForm("presidential pardon", "Target1");
        std::cout << GREEN << "Success: " << RESET << *form;
        delete form;  // Don't forget to clean up!
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 3: Create Robotomy Request Form
    std::cout << CYAN << "\nTesting Robotomy Request Form creation..." << RESET << std::endl;
    try {
        AForm* form = intern.makeForm("robotomy request", "Target2");
        std::cout << GREEN << "Success: " << RESET << *form;
        delete form;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 4: Create Shrubbery Creation Form
    std::cout << CYAN << "\nTesting Shrubbery Creation Form creation..." << RESET << std::endl;
    try {
        AForm* form = intern.makeForm("shrubbery creation", "Target3");
        std::cout << GREEN << "Success: " << RESET << *form;
        delete form;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 5: Try to create invalid form
    std::cout << CYAN << "\nTesting invalid form creation..." << RESET << std::endl;
    try {
        AForm* form = intern.makeForm("invalid form", "Target4");
        delete form;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    std::cout << BOLD << BLUE << "\n=== Complete Workflow Tests ===" << RESET << std::endl;

    // Test 6: Complete workflow test
    std::cout << CYAN << "\nTesting complete workflow..." << RESET << std::endl;
    {
        Bureaucrat boss("Boss", 1);  // Highest rank
        Bureaucrat intern_worker("Intern", 150);  // Lowest rank
        AForm* form = intern.makeForm("presidential pardon", "Target5");

        std::cout << YELLOW << "\nTrying to execute unsigned form..." << RESET << std::endl;
        try {
            boss.executeForm(*form);
        } catch (std::exception& e) {
            std::cout << RED << "Exception: " << e.what() << RESET << std::endl;
        }

        std::cout << YELLOW << "\nHaving low-level intern sign form..." << RESET << std::endl;
        try {
            intern_worker.signForm(*form);
        } catch (std::exception& e) {
            std::cout << RED << "Exception: " << e.what() << RESET << std::endl;
        }

        std::cout << YELLOW << "\nHaving boss sign form..." << RESET << std::endl;
        try {
            boss.signForm(*form);
        } catch (std::exception& e) {
            std::cout << RED << "Exception: " << e.what() << RESET << std::endl;
        }

        std::cout << YELLOW << "\nHaving low-level intern execute form..." << RESET << std::endl;
        try {
            intern_worker.executeForm(*form);
        } catch (std::exception& e) {
            std::cout << RED << "Exception: " << e.what() << RESET << std::endl;
        }

        std::cout << YELLOW << "\nHaving boss execute form..." << RESET << std::endl;
        try {
            boss.executeForm(*form);
        } catch (std::exception& e) {
            std::cout << RED << "Exception: " << e.what() << RESET << std::endl;
        }

        delete form;
    }

    std::cout << BOLD << BLUE << "\n=== PDF Example Test ===" << RESET << std::endl;

        // Test 7: PDF example code
        std::cout << CYAN << "\nTesting example from PDF (Bender robotomy)..." << RESET << std::endl;
        {
            try {
                Intern someRandomIntern;
                AForm* rrf;

                std::cout << YELLOW << "Creating robotomy form for Bender..." << RESET << std::endl;
                rrf = someRandomIntern.makeForm("robotomy request", "Bender");

                // Let's also test the form to see it in action
                Bureaucrat boss("Big Boss", 1);
                std::cout << YELLOW << "\nHaving boss sign and execute the form..." << RESET << std::endl;
                boss.signForm(*rrf);
                boss.executeForm(*rrf);

                delete rrf;  // Don't forget to clean up!
            }
            catch (std::exception& e) {
                std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
            }
        }

    return 0;
}