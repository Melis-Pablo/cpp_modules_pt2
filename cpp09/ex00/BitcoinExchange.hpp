#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map> // For std::map
#include <string> // For std::string
#include <iostream> // For std::cout
#include <fstream> // For file operations
#include <cstdlib> // For atof
#include <cctype> // For isdigit

class BitcoinExchange {
    private:
        std::map<std::string, float> _database;

    public:
        // Canonical form
        BitcoinExchange(); // Default constructor
        BitcoinExchange(const BitcoinExchange &rhs); // Copy constructor
        BitcoinExchange &operator=(const BitcoinExchange &rhs); // Assignment operator
        ~BitcoinExchange(); // Destructor

        // Member functions
        void loadDatabase(const std::string &filename);
        void processInputFile(const std::string &filename);
        float getExchangeRate(const std::string &date) const;
        bool isValidDate(const std::string &date) const;
        bool isValidValue(const float value) const;

        // Custom exceptions
        class FileOpenException : public std::exception {
            public:
                const char *what() const throw();
        };
};

#endif