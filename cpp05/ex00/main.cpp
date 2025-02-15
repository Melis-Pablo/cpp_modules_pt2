#include "Bureaucrat.hpp"

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
   std::cout << BOLD << BLUE << "\n=== Constructor Tests ===" << RESET << std::endl;

   // Test 1: Create with valid grade 150 (minimum)
   std::cout << CYAN << "\nTesting minimum grade (150)..." << RESET << std::endl;
   try {
       Bureaucrat b1("John", 150);
       std::cout << GREEN << "Success: " << RESET << b1;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 2: Create with valid grade 1 (maximum)
   std::cout << CYAN << "\nTesting maximum grade (1)..." << RESET << std::endl;
   try {
       Bureaucrat b2("Alfred", 1);
       std::cout << GREEN << "Success: " << RESET << b2;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 3: Create with valid grade 75 (middle)
   std::cout << CYAN << "\nTesting middle grade (75)..." << RESET << std::endl;
   try {
       Bureaucrat b3("Kevin", 75);
       std::cout << GREEN << "Success: " << RESET << b3;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 4: Create with invalid grade 151 (too low)
   std::cout << CYAN << "\nTesting too low grade (151)..." << RESET << std::endl;
   try {
       Bureaucrat b4("Jeff", 151);
       std::cout << b4;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 5: Create with invalid grade 0 (too high)
   std::cout << CYAN << "\nTesting too high grade (0)..." << RESET << std::endl;
   try {
       Bureaucrat b5("Link", 0);
       std::cout << b5;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 6: Create with extreme invalid grades
   std::cout << CYAN << "\nTesting extreme invalid grades..." << RESET << std::endl;
   try {
       Bureaucrat b6("Bob", -5);
       std::cout << b6;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   std::cout << BOLD << BLUE << "\n=== Copy/Assignment Tests ===" << RESET << std::endl;

   // Test 7: Copy constructor with grade 1
   std::cout << CYAN << "\nTesting copy constructor with highest grade..." << RESET << std::endl;
   try {
       Bureaucrat original("Alice", 1);
       Bureaucrat copy(original);
       std::cout << GREEN << "Original: " << RESET << original;
       std::cout << GREEN << "Copy: " << RESET << copy;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 8: Copy constructor with grade 150
   std::cout << CYAN << "\nTesting copy constructor with lowest grade..." << RESET << std::endl;
   try {
       Bureaucrat original("Bob", 150);
       Bureaucrat copy(original);
       std::cout << GREEN << "Original: " << RESET << original;
       std::cout << GREEN << "Copy: " << RESET << copy;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 9-10: Assignment operator tests
   std::cout << CYAN << "\nTesting assignment operator..." << RESET << std::endl;
   try {
       Bureaucrat b1("Charlie", 42);
       Bureaucrat b2("David", 100);
       std::cout << YELLOW << "Before assignment:" << RESET << std::endl;
       std::cout << "b1: " << b1;
       std::cout << "b2: " << b2;

       b2 = b1;
       std::cout << GREEN << "After assignment:" << RESET << std::endl;
       std::cout << "b1: " << b1;
       std::cout << "b2: " << b2;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   std::cout << BOLD << BLUE << "\n=== Grade Increment Tests ===" << RESET << std::endl;

   // Test 11: Increment from 150 to 149
   std::cout << CYAN << "\nTesting increment from lowest grade..." << RESET << std::endl;
   try {
       Bureaucrat b("Eve", 150);
       std::cout << YELLOW << "Before increment: " << RESET << b;
       b.incrementGrade();
       std::cout << GREEN << "After increment: " << RESET << b;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 12: Increment from 75 to 74
   std::cout << CYAN << "\nTesting increment from middle grade..." << RESET << std::endl;
   try {
       Bureaucrat b("Frank", 75);
       std::cout << YELLOW << "Before increment: " << RESET << b;
       b.incrementGrade();
       std::cout << GREEN << "After increment: " << RESET << b;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 13-14: Increment at upper boundary
   std::cout << CYAN << "\nTesting increment at upper boundary..." << RESET << std::endl;
   try {
       Bureaucrat b("George", 1);
       std::cout << YELLOW << "Before increment: " << RESET << b;
       b.incrementGrade();
       std::cout << GREEN << "After increment: " << RESET << b;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   std::cout << BOLD << BLUE << "\n=== Grade Decrement Tests ===" << RESET << std::endl;

   // Test 15: Decrement from 1 to 2
   std::cout << CYAN << "\nTesting decrement from highest grade..." << RESET << std::endl;
   try {
       Bureaucrat b("Henry", 1);
       std::cout << YELLOW << "Before decrement: " << RESET << b;
       b.decrementGrade();
       std::cout << GREEN << "After decrement: " << RESET << b;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 16: Decrement from 75 to 76
   std::cout << CYAN << "\nTesting decrement from middle grade..." << RESET << std::endl;
   try {
       Bureaucrat b("Ivy", 75);
       std::cout << YELLOW << "Before decrement: " << RESET << b;
       b.decrementGrade();
       std::cout << GREEN << "After decrement: " << RESET << b;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   // Test 17-18: Decrement at lower boundary
   std::cout << CYAN << "\nTesting decrement at lower boundary..." << RESET << std::endl;
   try {
       Bureaucrat b("Jack", 150);
       std::cout << YELLOW << "Before decrement: " << RESET << b;
       b.decrementGrade();
       std::cout << GREEN << "After decrement: " << RESET << b;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   std::cout << BOLD << BLUE << "\n=== Output Format Tests ===" << RESET << std::endl;

   // Tests 19-21: Output format for different grades
   std::cout << CYAN << "\nTesting output format for various grades..." << RESET << std::endl;
   try {
       Bureaucrat b1("Kim", 1);
       Bureaucrat b2("Lee", 75);
       Bureaucrat b3("Mike", 150);
       std::cout << GREEN << "Highest grade: " << RESET << b1;
       std::cout << GREEN << "Middle grade: " << RESET << b2;
       std::cout << GREEN << "Lowest grade: " << RESET << b3;
   } catch (std::exception& e) {
       std::cout << RED << "Exception caught: " << e.what() << RESET << std::endl;
   }

   return 0;
}