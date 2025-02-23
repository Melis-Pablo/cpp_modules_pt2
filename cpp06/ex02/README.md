# Runtime Type Identification in C++

## Overview
This guide explores runtime type identification (RTTI) in C++98, focusing on dynamic casting and type checking in polymorphic class hierarchies. You will learn about safe type conversion and identification of derived classes through base class pointers and references.

## Core Concepts
- Dynamic Casting
- Virtual Functions
- Runtime Type Information
- Reference vs Pointer Type Checking
- Polymorphic Class Hierarchies

## Concepts Explained

### Dynamic Casting
Brief definition: A runtime casting mechanism used to safely convert pointers and references of a base class to its derived classes.

**Key Points:**
- Only works with polymorphic classes (classes with virtual functions)
- Returns nullptr for pointers if cast fails
- Throws std::bad_cast for references if cast fails
- Safer than static_cast for downcasting

**Example:**
```cpp
class Base { public: virtual ~Base() {} };
class Derived : public Base {};

Base* ptr = new Derived();
if (Derived* d = dynamic_cast<Derived*>(ptr))
    // Cast successful
else
    // Cast failed
```

### Reference vs Pointer RTTI
Brief definition: Different mechanisms for type checking and conversion between references and pointers in polymorphic hierarchies.

**Key Points:**
- Pointers return nullptr on failure
- References throw exceptions on failure
- References cannot be null
- Exception handling required for references

**Example:**
```cpp
// Pointer version
void checkType(Base* ptr) {
    if (dynamic_cast<Derived1*>(ptr))
        // It's Derived1
    else if (dynamic_cast<Derived2*>(ptr))
        // It's Derived2
}

// Reference version
void checkType(Base& ref) {
    try {
        (void)dynamic_cast<Derived1&>(ref);
        // It's Derived1
    } catch (std::bad_cast&) {
        try {
            (void)dynamic_cast<Derived2&>(ref);
            // It's Derived2
        } catch (std::bad_cast&) {
            // Neither type
        }
    }
}
```

### Virtual Destructors
Brief definition: Ensures proper cleanup of derived class objects through base class pointers.

**Key Points:**
- Required for polymorphic classes
- Enables safe deletion through base pointers
- Part of virtual dispatch mechanism
- Necessary for RTTI functionality

**Example:**
```cpp
class Base {
public:
    virtual ~Base() {}  // Makes class polymorphic
};

class Derived : public Base {
    // Will be properly destroyed even through Base pointer
};
```

## Implementation Notes
- Always make base classes polymorphic with virtual destructor
- Handle null pointers in pointer-based type checking
- Use try-catch blocks for reference-based type checking
- Clean up dynamically allocated objects
- Consider exception safety in reference handling
- Test all possible type combinations
- Verify random distribution in type generation

## Related Topics
- Virtual Functions and Polymorphism
- Exception Handling
- Memory Management
- Type Safety
- Object-Oriented Design Patterns
- Smart Pointers

## Common Pitfalls
1. Type Checking:
   - Forgetting virtual destructor
   - Not handling null pointers
   - Missing try-catch blocks for references

2. Memory Management:
   - Memory leaks in type generation
   - Not deleting dynamically created objects
   - Incorrect cleanup in exception cases

3. Design Issues:
   - Over-reliance on type checking
   - Breaking encapsulation
   - Tight coupling between classes

## Best Practices
1. Class Design:
   - Always declare destructors virtual in base classes
   - Keep inheritance hierarchies simple
   - Use RTTI only when necessary

2. Error Handling:
   - Always check for null pointers
   - Use proper exception handling
   - Provide meaningful error messages

3. Memory Management:
   - Clean up allocated resources
   - Consider using smart pointers
   - Implement proper copy semantics

4. Testing:
   - Test all possible type combinations
   - Verify proper memory cleanup
   - Check exception handling
   - Validate type identification accuracy