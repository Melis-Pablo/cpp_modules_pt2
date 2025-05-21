#include "PmergeMe.hpp"
#include <algorithm>
#include <ctime>
#include <sys/time.h>
#include <cmath>
#include <utility>

// Color definitions as per the Testing Framework
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Failed tests
#define GREEN   "\033[32m"      // Passed tests
#define YELLOW  "\033[33m"      // Section headers
#define BLUE    "\033[34m"      // Expected exceptions/warnings
#define CYAN    "\033[36m"      // Informational output

// Canonical form
PmergeMe::PmergeMe() {
    std::cout << RED << "=== STARTED PMERGEME ===" << RESET << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe &rhs) {
    *this = rhs;
    std::cout << RED << "=== COPY CONSTRUCTED PMERGEME ===" << RESET << std::endl; 
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
    if (this != &rhs) {
        _vec = rhs._vec;
        _list = rhs._list;
        _unsortedVec = rhs._unsortedVec;
    }
    std::cout << RED << "=== ASSIGNMENT OPERATOR PMERGEME ===" << RESET << std::endl;
    return *this;
}

PmergeMe::~PmergeMe() {
    std::cout << RED << "=== STOPPED PMERGEME ===" << RESET << std::endl;
}

// Helper function to get microseconds
double getTimeInMicroseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    std::cout << BLUE << "Getting Time:" << RESET << (tv.tv_sec * 1000000 + tv.tv_usec) << std::endl;
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

// Vector implementation of the Ford-Johnson algorithm (Merge-insertion sort)
void PmergeMe::mergeSortInsertVector(std::vector<int>& vec) {
    // Base case: Empty or single element is already sorted
    if (vec.size() <= 1) {
        std::cout << RED << "=== UNSORTABLE: 0-1 ITEMS ===" << RESET << std::endl;
        return;
    }

    // Step 1: Create pairs and order them
    std::vector<std::pair<int, int> > pairs;
    bool hasOddElement = (vec.size() % 2 != 0);
    int oddElement = 0;

    if (hasOddElement) {
        oddElement = vec.back();
        vec.pop_back();
        std::cout << CYAN << "=== CONTAINER HAS ODD ELEMENTS ===" << RESET << oddElement << std::endl;
    }

    for (size_t i = 0; i < vec.size(); i += 2) {
        if (vec[i] > vec[i + 1]) {
            std::swap(vec[i], vec[i + 1]);
        }
        pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
    }

    // Step 2: Extract larger elements for recursive sorting
    std::vector<int> largerElements;
    for (size_t i = 0; i < pairs.size(); i++) {
        largerElements.push_back(pairs[i].second);
    }

    // Recursively sort the larger elements
    mergeSortInsertVector(largerElements);

    // Step 3: Initialize the result with first pair's smaller element and all sorted larger elements
    std::vector<int> result;
    result.push_back(pairs[0].first);
    for (size_t i = 0; i < largerElements.size(); i++) {
        result.push_back(largerElements[i]);
    }

    // Step 4: Insert smaller elements using binary search for optimal insertion points
    // Insertion sequence defined by "jacobsthal numbers" in Ford-Johnson algorithm
    for (size_t i = 1; i < pairs.size(); i++) {
        int element = pairs[i].first;

        // Find insertion position using binary search
        std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.begin() + i + 1, element);
        result.insert(pos, element);
    }

    // Handle odd element if there was one
    if (hasOddElement) {
        std::vector<int>::iterator pos = std::lower_bound(result.begin(), result.end(), oddElement);
        result.insert(pos, oddElement);
    }

    // Update the input vector with the sorted result
    vec = result;
}

// List implementation of the Ford-Johnson algorithm
void PmergeMe::mergeSortInsertList(std::list<int>& lst) {
    // Base case: Empty or single element is already sorted
    if (lst.size() <= 1) {
        return;
    }

    // Step 1: Create pairs and order them
    std::list<std::pair<int, int> > pairs;
    bool hasOddElement = (lst.size() % 2 != 0);
    int oddElement = 0;

    if (hasOddElement) {
        oddElement = lst.back();
        lst.pop_back();
    }

    std::list<int>::iterator it = lst.begin();
    while (it != lst.end()) {
        int first = *it++;
        int second = *it++;

        if (first > second) {
            std::swap(first, second);
        }
        pairs.push_back(std::make_pair(first, second));
    }

    // Step 2: Extract larger elements for recursive sorting
    std::list<int> largerElements;
    for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        largerElements.push_back(it->second);
    }

    // Recursively sort the larger elements
    mergeSortInsertList(largerElements);

    // Step 3: Initialize the result with first pair's smaller element and all sorted larger elements
    std::list<int> result;
    result.push_back(pairs.front().first);
    result.insert(result.end(), largerElements.begin(), largerElements.end());

    // Step 4: Insert smaller elements at optimal positions
    std::list<std::pair<int, int> >::iterator pairIt = pairs.begin();
    ++pairIt; // Skip the first pair as its smaller element is already in result

    while (pairIt != pairs.end()) {
        int element = pairIt->first;

        // Find insertion position
        std::list<int>::iterator pos = result.begin();
        while (pos != result.end() && *pos < element) {
            ++pos;
        }

        result.insert(pos, element);
        ++pairIt;
    }

    // Handle odd element if there was one
    if (hasOddElement) {
        std::list<int>::iterator pos = result.begin();
        while (pos != result.end() && *pos < oddElement) {
            ++pos;
        }
        result.insert(pos, oddElement);
    }

    // Update the input list with the sorted result
    lst = result;
}

// Process command-line arguments and validate input
bool PmergeMe::processInput(int argc, char **argv) {
    if (argc < 2) {
        return false;
    }

    _vec.clear();
    _list.clear();
    _unsortedVec.clear();

    // Parse and validate arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        // Check if argument is a valid positive integer
        for (size_t j = 0; j < arg.length(); j++) {
            if (j == 0 && arg[j] == '-') {
                throw NegativeNumberException();
            }
            if (!isdigit(arg[j])) {
                throw InvalidNumberException();
            }
        }

        // Convert to integer
        int value = atoi(arg.c_str());

        _vec.push_back(value);
        _list.push_back(value);
    }

    // Store unsorted vector for display
    _unsortedVec = _vec;

    return true;
}

// Measure time for vector sort
double PmergeMe::measureVectorSort(const std::vector<int>& input) {
    std::vector<int> testVec = input;

    std::cout << std::endl << YELLOW << "=== " << "STARTED VECTOR MODE" << " ===" << RESET << std::endl;
    double startTime = getTimeInMicroseconds();
    mergeSortInsertVector(testVec);
    double endTime = getTimeInMicroseconds();
    std::cout << std::endl << YELLOW << "=== " << "FINISHED VECTOR MODE" << " ===" << RESET << std::endl;

    _vec = testVec; // Store the sorted result

    return endTime - startTime;
}

// Measure time for list sort
double PmergeMe::measureListSort(const std::list<int>& input) {
    std::list<int> testList = input;

    std::cout << std::endl << YELLOW << "=== " << "STARTED LIST MODE" << " ===" << RESET << std::endl;
    double startTime = getTimeInMicroseconds();
    mergeSortInsertList(testList);
    double endTime = getTimeInMicroseconds();
    std::cout << std::endl << YELLOW << "=== " << "FINISHED LIST MODE" << " ===" << RESET << std::endl;

    _list = testList; // Store the sorted result

    return endTime - startTime;
}

// Display sequence of numbers
void PmergeMe::displaySequence(const std::vector<int>& seq) {
    for (size_t i = 0; i < seq.size(); i++) {
        std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
}

// Sort and measure time for both containers
void PmergeMe::sortAndMeasure() {
    // Convert vector to list for initial list
    _list.clear();
    std::cout << BLUE << "=== CLEARED LIST ===" << RESET << std::endl;
    std::cout << BLUE << "=== FILLED LIST ===" << RESET << std::endl;
    _list.insert(_list.end(), _unsortedVec.begin(), _unsortedVec.end());

    // Display before state
    std::cout << BLUE << "=== BEFORE ===" << RESET << std::endl;
    displaySequence(_unsortedVec);

    // Sort and measure
    double vecTime = measureVectorSort(_unsortedVec);
    double listTime = measureListSort(_list);

    // Display after state
    std::cout << BLUE << "=== AFTER ===" << RESET << std::endl;
    displaySequence(_vec);

    // Display timing results
    displayResults(vecTime, listTime);
}

// Display timing results
void PmergeMe::displayResults(double vecTime, double listTime) {
    std::cout << std::fixed << std::setprecision(5);
    std::cout << BLUE << "Time to process a range of " << _vec.size() << " elements with std::vector : "
              << RESET << vecTime << " us" << std::endl;
    std::cout << BLUE << "Time to process a range of " << _list.size() << " elements with std::list : "
              << RESET << listTime << " us" << std::endl;
}

// Custom exception for negative numbers
const char *PmergeMe::NegativeNumberException::what() const throw() {
    std::cout << BLUE << "=== Negative numbers are not allowed. ===" << RESET << std::endl;
    return "";
}
// Custom exception for invalid numbers
const char *PmergeMe::InvalidNumberException::what() const throw() {
    std::cout << BLUE << "=== Invalid number format. ===" << RESET << std::endl;
    return "";
}