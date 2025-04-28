#ifndef RPN_HPP
#define RPN_HPP

#include <stack> // For stack operations
#include <string> // For string operations
#include <exception> // For exception handling
#include <cctype> // For character classification
#include <sstream> // For string stream operations
#include <cstdlib> // For atoi
#include <iostream> // For input/output operations

class RPN {
    private:
        std::stack<int> _operandStack;

    public:
        // Canonical form
        RPN(); // Default constructor
        RPN(const RPN &rhs); // Copy constructor
        RPN &operator=(const RPN &rhs); // Assignment operator
        ~RPN(); // Destructor

        // Member functions
        int evaluate(const std::string &expression);

        // Helper functions
        bool isOperator(char c) const;
        int performOperation(int a, int b, char op) const;

        // Custom exceptions
        class SyntaxErrorException : public std::exception {
            public:
                const char *what() const throw();
        };
};

#endif