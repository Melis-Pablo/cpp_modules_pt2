# C++ Modules (05-09)

## Introduction

This repository contains five advanced C++ modules from the 42 curriculum, building upon the foundational knowledge established in modules 00-04. These modules focus on more complex Object-Oriented Programming concepts and practical applications in C++.

These modules comply with the C++98 standard and continue the progressive learning journey through C++ features and design patterns.

## Module Overview

### [Module 05: Repetition and Exceptions](./cpp05)

An introduction to exception handling in C++, implemented through a bureaucratic nightmare simulation.

**Key concepts:**
- Exception classes
- Try/catch blocks
- Exception propagation
- Error handling patterns
- Custom exception hierarchies
- Form validation and processing

### [Module 06: C++ Casts](./cpp06)

Understanding the different casting mechanisms available in C++.

**Key concepts:**
- Static cast
- Dynamic cast
- Reinterpret cast
- Const cast
- Type conversion
- Scalar type conversions
- Serialization/Deserialization
- Type identification

### [Module 07: C++ Templates](./cpp07)

Learning template programming fundamentals and creating generic code.

**Key concepts:**
- Function templates
- Class templates
- Template specialization
- Template instantiation
- Generic algorithms
- Template parameter deduction
- Array template implementation

### [Module 08: Templated Containers, Iterators, Algorithms](./cpp08)

Working with container abstractions, iterators, and algorithm design.

**Key concepts:**
- STL containers
- Iterators
- Iterator design patterns
- Range-based operations
- Container adaptors
- Mutant stack implementation
- Finding algorithms

### [Module 09: STL (Standard Template Library)](./cpp09)

Practical applications using the Standard Template Library.

**Key concepts:**
- Container selection
- STL algorithms
- Data processing
- Parsing and validation
- Ford-Johnson merge-insertion sort
- Reverse Polish Notation
- Performance measurement

## Compilation and Usage

Each module contains multiple exercises, each with its own Makefile. To compile an exercise:

```bash
cd cpp_module_XX/exYY
make
```

This will create an executable that you can run to test the functionality.

## Requirements

- C++ compiler with C++98 support (g++, clang++)
- Make

All code must compile with:
```bash
c++ -Wall -Wextra -Werror -std=c++98
```

## Common Guidelines

Throughout these modules, the following rules apply:

- Orthodox Canonical Form for classes (unless stated otherwise)
- Memory management must be handled properly with no leaks
- No use of forbidden functions or libraries
- Include guards for all header files
- Clean, well-structured, and readable code
- Proper error handling

## Notes

- STL containers and algorithms are only allowed in Modules 08 and 09
- Each module introduces specific constraints and requirements
- The exercises progressively build upon previous knowledge
- These modules represent advanced C++ concepts and require solid understanding of the language basics