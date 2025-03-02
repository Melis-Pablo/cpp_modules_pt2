#include "RPN.hpp"
#include <cctype>
#include <sstream>
#include <cstdlib>

// Canonical form
RPN::RPN() {}

RPN::RPN(const RPN &rhs) {
    *this = rhs;
}

RPN &RPN::operator=(const RPN &rhs) {
    if (this != &rhs) {
        _operandStack = rhs._operandStack;
    }
    return *this;
}

RPN::~RPN() {}

// Member functions
int RPN::evaluate(const std::string &expression) {
    std::istringstream iss(expression);
    std::string token;

    // Clear the stack before evaluation
    while (!_operandStack.empty()) {
        _operandStack.pop();
    }

    while (iss >> token) {
        // If token is an operator
        if (token.length() == 1 && isOperator(token[0])) {
            // Need at least two operands for an operation
            if (_operandStack.size() < 2) {
                throw SyntaxErrorException();
            }

            // Pop the two most recent operands (reversed order for - and /)
            int b = _operandStack.top(); _operandStack.pop();
            int a = _operandStack.top(); _operandStack.pop();

            // Perform the operation and push the result
            _operandStack.push(performOperation(a, b, token[0]));
        }
        // If token is an operand
        else {
            // Check if token is a valid number
            for (size_t i = 0; i < token.length(); i++) {
                if (!isdigit(token[i])) {
                    throw SyntaxErrorException();
                }
            }

            int operand = std::atoi(token.c_str());
            // Numbers must be less than 10
            if (operand >= 10) {
                throw SyntaxErrorException();
            }

            _operandStack.push(operand);
        }
    }

    // After processing, there should be exactly one value in the stack
    if (_operandStack.size() != 1) {
        throw SyntaxErrorException();
    }

    return _operandStack.top();
}

bool RPN::isOperator(char c) const {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::performOperation(int a, int b, char op) const {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                throw SyntaxErrorException();
            }
            return a / b;
        default:
            throw SyntaxErrorException();
    }
}