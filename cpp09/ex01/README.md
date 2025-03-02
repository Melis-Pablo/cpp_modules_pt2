# Reverse Polish Notation

## Overview
This program evaluates mathematical expressions written in Reverse Polish Notation (RPN), where operators follow their operands. The implementation handles basic arithmetic operations and validates input expressions.

## Core Concepts
- Stack-based Expression Evaluation
- Reverse Polish Notation (Postfix Notation)
- STL Containers (std::stack)
- Parsing and Tokenization
- Error Handling

## Concepts Explained

### Reverse Polish Notation
- A mathematical notation where operators follow their operands
- **Key Points:**
  - Eliminates the need for parentheses
  - Easier to evaluate programmatically
  - Operations are performed as soon as an operator is encountered

**Example:**
```
Infix: 3 + 4 * 2 / (1 - 5)
RPN: 3 4 2 * 1 5 - / +
```

### Stack-based Evaluation
- Uses a stack data structure to evaluate expressions
- **Key Points:**
  - Push operands onto the stack
  - When an operator is encountered, pop the required operands
  - Perform the operation and push the result back

**Example:**
```cpp
std::stack<int> stack;
stack.push(3);
stack.push(4);
// When '+' is encountered:
int b = stack.top(); stack.pop(); // b = 4
int a = stack.top(); stack.pop(); // a = 3
stack.push(a + b); // stack now contains [7]
```

[Documentation Link](https://en.wikipedia.org/wiki/Reverse_Polish_notation)

### STL Stack Container
- A container adapter that provides LIFO (Last-In, First-Out) functionality
- **Key Points:**
  - Efficient push and pop operations
  - Access only to the top element
  - Based on an underlying container (default is std::deque)

**Example:**
```cpp
std::stack<int> stack;
stack.push(5);
stack.push(10);
int top = stack.top(); // top = 10
stack.pop(); // Stack now contains only 5
```

[Documentation Link](https://en.cppreference.com/w/cpp/container/stack)

## Implementation Notes
- Parses input expressions token by token using a stringstream
- Validates that all numbers are less than 10
- Handles all four basic operations: +, -, *, /
- Checks for common errors like insufficient operands
- Prevents division by zero
- Ensures the final result is the only value left on the stack
- Provides clear error messages for invalid expressions

## Related Topics
- Infix to Postfix Conversion
- Expression Parsing Algorithms
- Calculator Implementation
- Compiler Design Principles