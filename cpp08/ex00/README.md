# Generic Container Search

## Overview
Implementation of generic search functionality in STL containers using template functions and iterators. Demonstrates core concepts of template programming, STL algorithms, and iterator usage.

## Core Concepts
- Template Functions
- STL Algorithm std::find
- Container Iterators
- Exception Handling
- Type-safe Programming

## Concepts Explained

### Template Functions with Containers
- Functions that work with any container type by using templates
- Type-safe operations through iterator usage
- Container-independent implementation
- Key points:
  - Template parameter represents container type
  - Function parameters include container reference and search value
  - Return type uses container's iterator type

**Example:**
```cpp
template <typename Container>
typename Container::iterator find_element(Container& cont, int value) {
    // Implementation using container's iterator interface
}
```

### STL Algorithm std::find
- Part of STL algorithms library
- Performs linear search in a range of elements
- Works with any forward iterator
- Key points:
  - Takes begin and end iterators
  - Returns iterator to found element or end iterator
  - Time complexity: O(n)

**Example:**
```cpp
std::vector<int> vec;
std::vector<int>::iterator it = std::find(vec.begin(), vec.end(), value);
```

### Exception Handling in Templates
- Using exceptions for error conditions
- Consistent error reporting across different container types
- Standard exception hierarchy
- Key points:
  - std::runtime_error for runtime conditions
  - Meaningful error messages
  - Exception safety guarantees

**Example:**
```cpp
if (not_found_condition)
    throw std::runtime_error("Element not found in container");
```

### Iterator Usage
- Container-independent element access
- STL iterator concepts and requirements
- Common iterator operations
- Key points:
  - begin() and end() for range specification
  - Iterator comparison and dereferencing
  - Iterator arithmetic (when supported)

## Implementation Notes
- Always check container.end() for search failure
- Use typename keyword for dependent types
- Include proper headers (algorithm, stdexcept)
- Keep error messages descriptive and specific
- Template code should go in header files

## Related Topics
- STL Containers
- Generic Programming
- Type Traits
- Container Requirements
- Iterator Categories