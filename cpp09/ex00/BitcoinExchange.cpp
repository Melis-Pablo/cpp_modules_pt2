#include "BitcoinExchange.hpp"

// Canonical form
BitcoinExchange::BitcoinExchange() {} // Default constructor
BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs) { *this = rhs; } // Copy constructor
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) { (void)rhs; return *this; } // Assignment operator
BitcoinExchange::~BitcoinExchange() {} // Destructor

// Member functions
