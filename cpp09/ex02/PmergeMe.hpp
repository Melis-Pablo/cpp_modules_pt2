#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <cstdlib>
#include <exception>
#include <ctime>
#include <iomanip>
#include <sstream>

class PmergeMe {
    private:
        std::vector<int> _vec;
        std::list<int> _list;
        std::vector<int> _unsortedVec; // To store original input

        // Vector implementation
        void mergeSortInsertVector(std::vector<int>& vec);
        double measureVectorSort(const std::vector<int>& input);

        // List implementation
        void mergeSortInsertList(std::list<int>& lst);
        double measureListSort(const std::list<int>& input);

        // Helper functions
        template <typename Iterator>
        bool validateInput(Iterator begin, Iterator end);

        void displaySequence(const std::vector<int>& seq);

    public:
        // Canonical form
        PmergeMe(); // Default constructor
        PmergeMe(const PmergeMe &rhs); // Copy constructor
        PmergeMe &operator=(const PmergeMe &rhs); // Assignment operator
        ~PmergeMe(); // Destructor

        // Member functions
        bool processInput(int argc, char **argv);
        void sortAndMeasure();
        void displayResults(double vecTime, double listTime);

        // Custom exceptions
        class NegativeNumberException : public std::exception {
            public:
                const char *what() const throw();
        };

        class InvalidNumberException : public std::exception {
            public:
                const char *what() const throw();
        };
};

#endif