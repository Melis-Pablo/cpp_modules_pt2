#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>

// Standard color definitions for test files
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Failed tests
#define GREEN   "\033[32m"      // Passed tests
#define YELLOW  "\033[33m"      // Section headers
#define BLUE    "\033[34m"      // Expected exceptions/warnings
#define CYAN    "\033[36m"      // Informational output

void printHeader(const std::string& header) {
    std::cout << std::endl << YELLOW << "=== " << header << " ===" << RESET << std::endl;
}

void printTestResult(const std::string& testName, bool success) {
    std::cout << (success ? GREEN : RED) << testName << ": " << (success ? "PASS" : "FAIL") << RESET << std::endl;
}

int main() {
    // 1. PDF/Project Specific Tests
    {
        printHeader("Subject PDF Test");

        MutantStack<int> mstack;
        std::cout << CYAN << "Testing basic stack operations:" << RESET << std::endl;

        mstack.push(5);
        mstack.push(17);
        printTestResult("Push elements", mstack.top() == 17);

        mstack.pop();
        printTestResult("Pop element", mstack.size() == 1 && mstack.top() == 5);

        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        mstack.push(0);

        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();

        ++it;
        --it;

        std::cout << CYAN << "Iterating through stack:" << RESET << std::endl;
        std::vector<int> values;
        while (it != ite) {
            std::cout << *it << std::endl;
            values.push_back(*it);
            ++it;
        }

        std::stack<int> s(mstack);
        printTestResult("Convert to standard stack", s.size() == mstack.size());
    }

    // 2. Basic Functionality Tests
    {
        printHeader("Basic Stack Operations");

        MutantStack<int> stack;
        printTestResult("Empty stack size is 0", stack.size() == 0);

        stack.push(42);
        printTestResult("Size after push is 1", stack.size() == 1);
        printTestResult("Top element is correct", stack.top() == 42);

        stack.push(21);
        stack.pop();
        printTestResult("Size after pop is correct", stack.size() == 1);
        printTestResult("Top element after pop is correct", stack.top() == 42);
    }

    // 3. Iterator Functionality Tests
    {
        printHeader("Iterator Operations");

        MutantStack<int> stack;
        for(int i = 1; i <= 5; ++i)
            stack.push(i);

        // Basic iterator operations
        MutantStack<int>::iterator it = stack.begin();
        printTestResult("Begin points to first element", *it == 1);

        ++it;
        printTestResult("Iterator increment", *it == 2);

        --it;
        printTestResult("Iterator decrement", *it == 1);

        it = stack.end();
        --it;
        printTestResult("End iterator points past last element", *it == 5);

        // Const iterator tests
        const MutantStack<int> constStack(stack);
        MutantStack<int>::const_iterator cit = constStack.begin();
        printTestResult("Const iterator access", *cit == 1);

        // Iterator comparison
        MutantStack<int>::iterator it1 = stack.begin();
        MutantStack<int>::iterator it2 = stack.begin();
        printTestResult("Iterator comparison", it1 == it2);
    }

    // 4. Container Comparison Tests
    {
        printHeader("Container Compatibility");

        // Compare with std::list
        MutantStack<int> mstack;
        std::list<int> lst;

        // Add same elements
        for(int i = 1; i <= 5; ++i) {
            mstack.push(i);
            lst.push_back(i);
        }

        // Compare iteration results
        MutantStack<int>::iterator mit = mstack.begin();
        std::list<int>::iterator lit = lst.begin();

        bool iterationMatch = true;
        while(mit != mstack.end() && lit != lst.end()) {
            if(*mit != *lit) {
                iterationMatch = false;
                break;
            }
            ++mit;
            ++lit;
        }

        printTestResult("MutantStack matches list iteration", iterationMatch);
        printTestResult("Sizes match", mstack.size() == lst.size());
    }

    // 5. Object Behavior Tests
    {
        printHeader("Object Behavior");

        // Copy constructor
        MutantStack<int> original;
        original.push(1);
        original.push(2);

        MutantStack<int> copy(original);
        printTestResult("Copy constructor - sizes match", copy.size() == original.size());
        printTestResult("Copy constructor - elements match", copy.top() == original.top());

        // Assignment operator
        MutantStack<int> assigned;
        assigned = original;
        printTestResult("Assignment - sizes match", assigned.size() == original.size());
        printTestResult("Assignment - elements match", assigned.top() == original.top());

        // Independence after copy
        copy.push(3);
        printTestResult("Copies are independent", copy.size() != original.size());
    }

    // 6. Type Support Tests
    {
        printHeader("Different Type Support");

        // String stack
        MutantStack<std::string> strStack;
        strStack.push("Hello");
        strStack.push("World");

        printTestResult("String stack operation", strStack.top() == "World");

        // Float stack
        MutantStack<float> floatStack;
        floatStack.push(1.1f);
        floatStack.push(2.2f);

        printTestResult("Float stack operation", floatStack.top() == 2.2f);

        // Iteration through string stack
        std::string concatenated;
        for(MutantStack<std::string>::iterator it = strStack.begin(); it != strStack.end(); ++it) {
            concatenated += *it;
        }
        printTestResult("String stack iteration", concatenated == "HelloWorld");
    }

    return 0;
}