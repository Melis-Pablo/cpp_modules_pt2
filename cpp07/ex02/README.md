# Template Array Class Implementation

## Overview
A dynamic array implementation using class templates demonstrates key C++ concepts including memory management, operator overloading, exception handling, and template programming. This implementation provides type-safe array operations with proper resource management.

## Core Concepts
- Dynamic Memory Management
- Template Class Design
- Exception Safety
- Copy and Assignment Semantics
- Operator Overloading
- Const Correctness

## Concepts Explained

### Dynamic Memory Management
- Array data stored in heap memory
- Resource acquisition and release
- Prevention of memory leaks

**Key Points:**
- Use of new[] and delete[] operators
- Exception safety in memory operations
- Proper cleanup in destructor

### Template Class Implementation
- Header-only implementation required
- Type-independent array operations
- Support for both built-in and user-defined types

**Example:**
```cpp
template<typename T>
class Array {
    T* data;        // Dynamic array storage
    size_t size;    // Array size tracking
public:
    // Class interface
};
```

### Exception Safety
- Array bounds checking
- Memory allocation error handling
- Strong exception guarantee

**Key Points:**
- Custom exception classes
- Exception propagation
- Resource cleanup on exceptions

### Orthodox Canonical Form Implementation
- Default constructor
- Parameterized constructor
- Copy constructor
- Assignment operator
- Destructor

**Example:**
```cpp
template<typename T>
Array<T>::Array(const Array& other) :
    data(new T[other.size]), size(other.size) {
    for(size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}
```

## Implementation Notes

### Memory Management
- Never access unallocated memory
- Clean up resources in destructors
- Handle self-assignment properly
- Implement deep copying

### Array Access
- Provide bounds checking
- Support const and non-const access
- Use reference returns for efficiency

### Best Practices
- Use size_t for array indices
- Implement const member functions
- Separate interface and implementation
- Maintain exception safety guarantees

## Testing Guidelines

### Constructor Tests
```cpp
// Test empty array
Array<int> empty;
assert(empty.size() == 0);

// Test sized array
Array<int> sized(10);
assert(sized.size() == 10);
```

### Copy and Assignment Tests
```cpp
Array<int> original(5);
Array<int> copy(original);    // Test copy constructor
Array<int> assigned = copy;   // Test assignment operator
```

### Exception Tests
```cpp
try {
    array[-1];               // Test negative index
    array[array.size()];     // Test bounds overflow
} catch (const std::exception& e) {
    // Handle exception
}
```

### Memory Tests
```cpp
// Test for memory leaks
{
    Array<int> temp(1000);
    temp[0] = 42;
} // Destructor should clean up
```

## Common Pitfalls
- Forgetting to delete[] in destructor
- Shallow copying in copy constructor/assignment
- Not handling self-assignment
- Memory leaks in assignment operator
- Missing bounds checks
- Incorrect template implementation location

## Best Practices
- Always initialize pointers
- Use const member functions where appropriate
- Implement complete bounds checking
- Maintain strong exception safety
- Follow RAII principles
- Document template requirements
- Use meaningful exception messages