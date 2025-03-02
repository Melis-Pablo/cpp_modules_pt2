# PmergeMe

## Overview
This program implements the Ford-Johnson algorithm (merge-insert sort) to sort a sequence of positive integers. It compares the algorithm's performance using two different STL containers: std::vector and std::list.

## Core Concepts
- Ford-Johnson Algorithm (Merge-Insertion Sort)
- STL Containers (std::vector and std::list)
- Algorithm Performance Measurement
- Container Comparison
- Template Usage

## Concepts Explained

### Ford-Johnson Algorithm
- A hybrid sorting algorithm that combines merge sort and insertion sort
- **Key Points:**
  - Pairs up elements and orders them (smaller first)
  - Recursively sorts the sequence of larger elements
  - Inserts smaller elements at optimal positions
  - Known for minimizing the number of comparisons

**Example:**
```cpp
// Simplified example of Ford-Johnson algorithm
void mergeSortInsert(std::vector<int>& vec) {
    // Base case
    if (vec.size() <= 1) return;

    // Create ordered pairs
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < vec.size(); i += 2) {
        if (vec[i] > vec[i+1]) std::swap(vec[i], vec[i+1]);
        pairs.push_back(std::make_pair(vec[i], vec[i+1]));
    }

    // Sort larger elements recursively
    std::vector<int> largerElements;
    for (auto& pair : pairs) largerElements.push_back(pair.second);
    mergeSortInsert(largerElements);

    // Build result and insert smaller elements
    // ... further implementation details ...
}
```

[Documentation Link](https://en.wikipedia.org/wiki/Merge-insertion_sort)

### STL Vector Container
- Dynamic array with fast random access
- **Key Points:**
  - Contiguous memory allocation
  - Efficient random access (O(1))
  - Efficient insertion at the end (amortized O(1))
  - Inefficient insertion in the middle (O(n))

**Example:**
```cpp
std::vector<int> vec;
vec.push_back(5);     // Add element to end
int value = vec[0];   // Random access
vec.insert(vec.begin() + 1, 10); // Insert in middle
```

[Documentation Link](https://en.cppreference.com/w/cpp/container/vector)

### STL List Container
- Doubly-linked list
- **Key Points:**
  - Non-contiguous memory allocation
  - Slow random access (O(n))
  - Efficient insertion anywhere (O(1)) given an iterator
  - No reallocation needed when growing

**Example:**
```cpp
std::list<int> lst;
lst.push_back(5);     // Add element to end
std::list<int>::iterator it = lst.begin();
++it;                 // Move to second element
lst.insert(it, 10);   // Efficient insertion
```

[Documentation Link](https://en.cppreference.com/w/cpp/container/list)

## Implementation Notes
- The Ford-Johnson algorithm is implemented separately for each container
- Time measurement is done with microsecond precision
- For std::list, binary search is replaced with linear search due to lack of random access
- The program validates all input numbers are positive integers
- Error messages are displayed for invalid input
- Performance comparison may vary based on input size and system

## Related Topics
- Big O notation and algorithm complexity
- Sorting algorithm comparisons
- Container selection based on usage patterns
- Time complexity vs. space complexity trade-offs