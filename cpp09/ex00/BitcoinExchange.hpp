#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib> // For atof

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
                const char *what() const throw() { return "Error: could not open file."; }
        };
};

#endif