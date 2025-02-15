#include "Bureaucrat.hpp"
#include "Form.hpp"

// Color codes
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
    std::cout << BOLD << BLUE << "\n=== Form Constructor Tests ===" << RESET << std::endl;

    // Test 1: Create form with minimum valid grades (150)
    std::cout << CYAN << "\nTesting minimum valid grades (sign:150, exec:150)..." << RESET << std::endl;
    try {
        Form f1("Basic Form", 150, 150);
        std::cout << GREEN << "Success: " << RESET << f1 << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 2: Create form with maximum valid grades (1)
    std::cout << CYAN << "\nTesting maximum valid grades (sign:1, exec:1)..." << RESET << std::endl;
    try {
        Form f2("Top Secret", 1, 1);
        std::cout << GREEN << "Success: " << RESET << f2 << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 3: Create form with mixed valid grades
    std::cout << CYAN << "\nTesting mixed valid grades (sign:75, exec:25)..." << RESET << std::endl;
    try {
        Form f3("Mixed Level", 75, 25);
        std::cout << GREEN << "Success: " << RESET << f3 << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 4: Create form with sign grade too high
    std::cout << CYAN << "\nTesting sign grade too high (sign:0, exec:75)..." << RESET << std::endl;
    try {
        Form f4("Invalid Sign", 0, 75);
        std::cout << f4 << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 5: Create form with exec grade too high
    std::cout << CYAN << "\nTesting exec grade too high (sign:75, exec:0)..." << RESET << std::endl;
    try {
        Form f5("Invalid Exec", 75, 0);
        std::cout << f5 << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 6: Create form with sign grade too low
    std::cout << CYAN << "\nTesting sign grade too low (sign:151, exec:75)..." << RESET << std::endl;
    try {
        Form f6("Invalid Sign Low", 151, 75);
        std::cout << f6 << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 7: Create form with exec grade too low
    std::cout << CYAN << "\nTesting exec grade too low (sign:75, exec:151)..." << RESET << std::endl;
    try {
        Form f7("Invalid Exec Low", 75, 151);
        std::cout << f7 << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    std::cout << BOLD << BLUE << "\n=== Form Copy Tests ===" << RESET << std::endl;

    // Test 8: Copy unsigned form
    std::cout << CYAN << "\nTesting copy of unsigned form..." << RESET << std::endl;
    try {
        Form original("Original", 75, 75);
        Form copy(original);
        std::cout << GREEN << "Original: " << RESET << original << std::endl;
        std::cout << GREEN << "Copy: " << RESET << copy << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 9: Assignment operator
    std::cout << CYAN << "\nTesting assignment operator..." << RESET << std::endl;
    try {
        Form f1("Form One", 50, 50);
        Form f2("Form Two", 100, 100);
        std::cout << YELLOW << "Before assignment:" << RESET << std::endl;
        std::cout << "f1: " << f1 << std::endl;
        std::cout << "f2: " << f2 << std::endl;

        f2 = f1;
        std::cout << GREEN << "After assignment:" << RESET << std::endl;
        std::cout << "f1: " << f1 << std::endl;
        std::cout << "f2: " << f2 << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    std::cout << BOLD << BLUE << "\n=== Form Signing Tests ===" << RESET << std::endl;

    // Test 10: Valid signing (bureaucrat grade > required)
    std::cout << CYAN << "\nTesting valid signing (bureaucrat grade > required)..." << RESET << std::endl;
    try {
        Bureaucrat b("Bob", 1);
        Form f("Easy Form", 50, 50);
        std::cout << YELLOW << "Before signing:" << RESET << std::endl;
        std::cout << f << std::endl;
        b.signForm(f);
        std::cout << GREEN << "After signing:" << RESET << std::endl;
        std::cout << f << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 11: Valid signing (bureaucrat grade = required)
    std::cout << CYAN << "\nTesting valid signing (bureaucrat grade = required)..." << RESET << std::endl;
    try {
        Bureaucrat b("Charlie", 75);
        Form f("Equal Grade Form", 75, 75);
        std::cout << YELLOW << "Before signing:" << RESET << std::endl;
        std::cout << f << std::endl;
        b.signForm(f);
        std::cout << GREEN << "After signing:" << RESET << std::endl;
        std::cout << f << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 12: Invalid signing (bureaucrat grade too low)
    std::cout << CYAN << "\nTesting invalid signing (bureaucrat grade too low)..." << RESET << std::endl;
    try {
        Bureaucrat b("David", 100);
        Form f("Hard Form", 50, 50);
        std::cout << YELLOW << "Before signing:" << RESET << std::endl;
        std::cout << f << std::endl;
        b.signForm(f);
        std::cout << GREEN << "After signing:" << RESET << std::endl;
        std::cout << f << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 13: Signing already signed form
    std::cout << CYAN << "\nTesting signing already signed form..." << RESET << std::endl;
    try {
        Bureaucrat b("Eve", 1);
        Form f("Double Sign Form", 50, 50);
        std::cout << YELLOW << "First signing:" << RESET << std::endl;
        b.signForm(f);
        std::cout << f << std::endl;
        std::cout << YELLOW << "Second signing attempt:" << RESET << std::endl;
        b.signForm(f);
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    std::cout << BOLD << BLUE << "\n=== Edge Cases ===" << RESET << std::endl;

    // Test 14: Highest grade bureaucrat with lowest grade form
    std::cout << CYAN << "\nTesting highest grade bureaucrat with lowest grade form..." << RESET << std::endl;
    try {
        Bureaucrat b("Frank", 1);
        Form f("Easy Form", 150, 150);
        b.signForm(f);
        std::cout << GREEN << "Result: " << RESET << f << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 15: Lowest grade bureaucrat with highest grade form
    std::cout << CYAN << "\nTesting lowest grade bureaucrat with highest grade form..." << RESET << std::endl;
    try {
        Bureaucrat b("George", 150);
        Form f("Impossible Form", 1, 1);
        b.signForm(f);
        std::cout << GREEN << "Result: " << RESET << f << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    // Test 16: Assignment operator with signed form
    std::cout << CYAN << "\nTesting assignment operator with signed form..." << RESET << std::endl;
    try {
        Bureaucrat b("Admin", 1);
        Form f1("Form One", 50, 50);
        Form f2("Form Two", 100, 100);

        // Sign the first form
        b.signForm(f1);

        std::cout << YELLOW << "Before assignment:" << RESET << std::endl;
        std::cout << "f1 (signed): " << f1 << std::endl;
        std::cout << "f2 (unsigned): " << f2 << std::endl;

        f2 = f1;  // Assign signed form to unsigned form

        std::cout << GREEN << "After assignment:" << RESET << std::endl;
        std::cout << "f1: " << f1 << std::endl;
        std::cout << "f2: " << f2 << std::endl;
    } catch (std::exception& e) {
        std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
    }

    return 0;
}