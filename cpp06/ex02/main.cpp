#include "Identify.hpp"

// Color definitions
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Failed tests
#define GREEN   "\033[32m"      // Passed tests
#define YELLOW  "\033[33m"      // Section headers
#define BLUE    "\033[34m"      // Expected exceptions/warnings
#define CYAN    "\033[36m"      // Informational output

// Function declarations
Base* generate(void);
void identify(Base* p);
void identify(Base& p);

// Test utility functions
void printHeader(const std::string& header) {
    std::cout << std::endl << YELLOW << "=== " << header << " ===" << RESET << std::endl;
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? GREEN : RED)
              << testName << ": "
              << (success ? "PASS" : "FAIL")
              << RESET << std::endl;
}

void printSubHeader(const std::string& header) {
    std::cout << CYAN << "--- " << header << " ---" << RESET << std::endl;
}

// Test functions
void testDirectInstantiation() {
    printSubHeader("Direct Instantiation Tests");

    A a;
    B b;
    C c;

    std::cout << BLUE << "Testing A:" << RESET << std::endl;
    identify(&a);
    identify(a);

    std::cout << BLUE << "Testing B:" << RESET << std::endl;
    identify(&b);
    identify(b);

    std::cout << BLUE << "Testing C:" << RESET << std::endl;
    identify(&c);
    identify(c);
}

void testRandomGeneration() {
    printSubHeader("Random Generation Tests");

    // Count occurrences of each type
    int countA = 0, countB = 0, countC = 0;
    const int numTests = 100;

    for (int i = 0; i < numTests; i++) {
        Base* ptr = generate();
        std::cout << BLUE << "Generated type " << i + 1 << ": " << RESET;
        identify(ptr);

        // Count using pointer version
        if (dynamic_cast<A*>(ptr)) countA++;
        else if (dynamic_cast<B*>(ptr)) countB++;
        else if (dynamic_cast<C*>(ptr)) countC++;

        delete ptr;
    }

    std::cout << BLUE << "\nDistribution after " << numTests << " generations:" << RESET << std::endl;
    std::cout << "A: " << countA << " (" << (countA * 100.0 / numTests) << "%)" << std::endl;
    std::cout << "B: " << countB << " (" << (countB * 100.0 / numTests) << "%)" << std::endl;
    std::cout << "C: " << countC << " (" << (countC * 100.0 / numTests) << "%)" << std::endl;

    // Check if distribution is roughly even (within 15% of expected)
    bool evenDistribution = (countA > numTests * 0.18) && (countA < numTests * 0.48) &&
                          (countB > numTests * 0.18) && (countB < numTests * 0.48) &&
                          (countC > numTests * 0.18) && (countC < numTests * 0.48);

    printTestResult("Random distribution", evenDistribution);
}

void testNullPointer() {
    printSubHeader("Null Pointer Test");

    std::cout << BLUE << "Testing null pointer:" << RESET << std::endl;
    Base* nullPtr = NULL;
    identify(nullPtr);
}

void testConsistency() {
    printSubHeader("Pointer/Reference Consistency Tests");

    for (int i = 0; i < 10; i++) {
        Base* ptr = generate();
        std::cout << BLUE << "Test " << i + 1 << ":" << RESET << std::endl;
        std::cout << "Pointer version: ";
        identify(ptr);
        std::cout << "Reference version: ";
        identify(*ptr);
        delete ptr;
    }
}

int main() {
    // Seed random number generator
    srand(time(NULL));

    // PDF/Project Specific Tests
    {
        printHeader("Basic Type Identification");
        testDirectInstantiation();
    }

    // Random Generation Tests
    {
        printHeader("Random Generation");
        testRandomGeneration();
    }

    // Edge Cases
    {
        printHeader("Edge Cases");
        testNullPointer();
    }

    // Consistency Tests
    {
        printHeader("Consistency Tests");
        testConsistency();
    }

    return 0;
}