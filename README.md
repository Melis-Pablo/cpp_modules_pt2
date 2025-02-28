# C++ Modules (05-09)

## 🎓 Project Overview

This repository contains five advanced C++ modules from the 42 School curriculum, building upon the foundational concepts established in modules 00-04. These modules explore more sophisticated aspects of Object-Oriented Programming and practical C++ applications, taking you from exception handling to advanced STL usage.

All modules adhere to the C++98 standard, continuing the structured learning path through progressively complex C++ features and design patterns while maintaining backward compatibility.

## 📚 Module Contents

### [Module 05: Repetition and Exceptions](./cpp05)

A deep dive into C++ exception handling through a bureaucratic nightmare simulation.

**Key Concepts:**
- **Exception Hierarchy**: Creating and extending custom exception classes
- **Exception Flow**: Mastering try/catch blocks and exception propagation
- **Error Management**: Implementing robust error handling patterns
- **Form Processing**: Building systems for form validation and processing
- **Exception Safety**: Understanding the different levels of exception guarantees

### [Module 06: C++ Casts](./cpp06)

Mastering the various casting mechanisms that C++ offers for type conversion.

**Key Concepts:**
- **Static Cast**: Safe conversions between related types
- **Dynamic Cast**: Runtime type-checking for polymorphic classes
- **Reinterpret Cast**: Low-level binary reinterpretation between unrelated types
- **Const Cast**: Modifying const-qualified variables
- **Type Conversion**: Creating custom conversion operators and constructors
- **Scalar Conversions**: Converting between fundamental types
- **Binary Representation**: Understanding memory layout and serialization

### [Module 07: C++ Templates](./cpp07)

Exploring template programming to create flexible, generic code components.

**Key Concepts:**
- **Function Templates**: Creating type-independent functions
- **Class Templates**: Building generic, reusable class structures
- **Template Specialization**: Customizing behavior for specific types
- **Template Parameters**: Working with type and non-type parameters
- **Generic Algorithms**: Implementing algorithms that work with any data type
- **Array Implementation**: Creating a templated array container
- **Template Instantiation**: Understanding how templates generate code

### [Module 08: Templated Containers, Iterators, Algorithms](./cpp08)

Working with container abstractions, iterator patterns, and algorithm design.

**Key Concepts:**
- **STL Containers**: Using vector, list, map, and other standard containers
- **Iterator Design**: Creating and working with different iterator types
- **Container Traversal**: Efficiently processing container elements
- **Range Operations**: Performing operations across element ranges
- **Container Adaptors**: Using and extending stack, queue, and priority_queue
- **Mutant Stack**: Extending standard containers with new functionality
- **Search Algorithms**: Implementing efficient finding algorithms

### [Module 09: STL (Standard Template Library)](./cpp09)

Practical applications leveraging the full power of the Standard Template Library.

**Key Concepts:**
- **Container Selection**: Choosing the right container for specific tasks
- **Algorithm Application**: Using STL algorithms for data processing
- **Data Manipulation**: Parsing, validating, and transforming data
- **Merge-Insertion Sort**: Implementing the Ford-Johnson algorithm
- **Reverse Polish Notation**: Building an RPN calculator
- **Performance Analysis**: Measuring and optimizing algorithm efficiency
- **Real-world Applications**: Solving practical problems with STL

## 🛠️ Technical Implementation

### Development Standards

All code in these modules follows strict guidelines:
- **Orthodox Canonical Form**: Including the four essential class functions
- **Memory Management**: Proper allocation and deallocation to prevent leaks
- **Error Handling**: Robust exception management and input validation
- **Code Organization**: Clean structure with appropriate separation of concerns

### Compilation and Usage

Each module contains multiple exercises with individual Makefiles:

```bash
# Navigate to the exercise directory
cd cpp_module_XX/exYY

# Compile the exercise
make

# Run the executable
./executable_name
```

All code must compile with these flags:
```bash
c++ -Wall -Wextra -Werror -std=c++98
```

## 📝 Learning Outcomes

Through these advanced modules, I gained practical knowledge in:

- **Exception Handling**: Creating robust error management systems
- **Type Conversion**: Safely navigating C++'s type system
- **Generic Programming**: Building flexible, reusable code with templates
- **Container Design**: Understanding data structure implementation
- **Algorithm Efficiency**: Optimizing operations on collections of data
- **STL Mastery**: Leveraging C++'s powerful standard library
- **Problem Solving**: Approaching complex programming challenges systematically

## ⚠️ Notes and Constraints

- STL containers and algorithms are only permitted in Modules 08 and 09
- Each module introduces specific constraints that must be respected
- The exercises build progressively, with later modules assuming mastery of earlier concepts
- All code is written according to the C++98 standard, without modern C++ features

For detailed information about each module, refer to the individual READMEs within each module directory.

---

*These projects are part of the 42 School Common Core curriculum.*