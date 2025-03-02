# Bitcoin Exchange

## Overview
This program calculates the value of Bitcoin based on a specified date and amount. It reads exchange rates from a CSV database and processes user input files to determine the value of Bitcoin at different points in time.

## Core Concepts
- STL Containers (std::map)
- File I/O Operations
- Date Parsing and Validation
- Exception Handling
- CSV Data Processing

## Concepts Explained

### STL Map Container
- A sorted associative container that stores key-value pairs
- **Key Points:**
  - Keys are unique and automatically sorted
  - Efficient lookup with logarithmic time complexity O(log n)
  - Ideal for mapping dates to exchange rates

**Example:**
```cpp
std::map<std::string, float> database;
database["2021-01-01"] = 29000.0;
float rate = database["2021-01-01"]; // Retrieves 29000.0
```

[Documentation Link](https://en.cppreference.com/w/cpp/container/map)

### File I/O in C++
- Reading from and writing to files
- **Key Points:**
  - Use ifstream for input file operations
  - Always check if file opened successfully
  - Process content line by line with getline
  - Close files after use

**Example:**
```cpp
std::ifstream file("data.csv");
if (!file.is_open()) {
    throw std::exception();
}
std::string line;
while (std::getline(file, line)) {
    // Process line
}
file.close();
```

### Date Processing
- Validating and comparing date strings
- **Key Points:**
  - Check format compliance (YYYY-MM-DD)
  - Validate year, month, and day values
  - Handle special cases like leap years
  - Find closest previous date when exact match doesn't exist

**Example:**
```cpp
bool isValidDate(const std::string &date) {
    // Format check
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    // Extract and validate components
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    return isValidDateComponents(year, month, day);
}
```

## Implementation Notes
- The exchange rate database is stored in a std::map for efficient lookups
- When a date is not found in the database, the program uses the closest previous date's rate
- Input values must be positive and not exceed 1000
- Dates must follow the YYYY-MM-DD format and be valid calendar dates
- All error cases are handled with appropriate user-friendly messages

## Related Topics
- Binary search trees (underlying implementation of std::map)
- Time series data processing
- Financial data analysis
- Parsing strategies for structured text files