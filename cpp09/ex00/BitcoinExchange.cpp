#include "BitcoinExchange.hpp"

// Canonical form
BitcoinExchange::BitcoinExchange() {
    // Default constructor - initialize with default database
    try {
        loadDatabase("data.csv");
    } catch (const std::exception &e) {
        // Handle initialization failure silently
    }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs) {
    *this = rhs; // Call assignment operator
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
    if (this != &rhs) {
        _database = rhs._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {
    // No dynamic memory to free
}

// Member functions
void BitcoinExchange::loadDatabase(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw FileOpenException();
    }

    std::string line;
    // Skip header line
    std::getline(file, line);

    // Read each line and parse
    while (std::getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string date = line.substr(0, commaPos);
            std::string rateStr = line.substr(commaPos + 1);
            float rate = atof(rateStr.c_str());

            _database[date] = rate;
        }
    }
    file.close();
}

void BitcoinExchange::processInputFile(const std::string &filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw FileOpenException();
    }

    std::string line;
    // Skip header line if it exists
    std::getline(file, line);

    // Process each line
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        size_t pipePos = line.find(" | ");
        if (pipePos == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = line.substr(0, pipePos);
        std::string valueStr = line.substr(pipePos + 3);

        // Check if date format is valid
        if (!isValidDate(date)) {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }

        // Convert value to float
        float value = atof(valueStr.c_str());

        // Check value range
        if (value < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        // Get exchange rate and calculate result
        float rate = getExchangeRate(date);
        float result = value * rate;

        std::cout << date << " => " << value << " = " << result << std::endl;
    }
    file.close();
}

float BitcoinExchange::getExchangeRate(const std::string &date) const {
    // Find first element >= date
    std::map<std::string, float>::const_iterator it = _database.lower_bound(date);

    // If exact match, use it
    if (it != _database.end() && it->first == date) {
        return it->second;
    }

    // If not exact match, use previous (unless we're at beginning)
    if (it == _database.begin()) {
        return 0; // No valid rate found
    }

    --it; // Go to previous element
    return it->second;
}

bool BitcoinExchange::isValidDate(const std::string &date) const {
    // Basic format check: YYYY-MM-DD
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    // Check if all other characters are digits
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue; // Skip the hyphens
        if (!isdigit(date[i])) return false;
    }

    // Extract year, month, day
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    // Check ranges
    if (year < 0) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    // Check days in month
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    } else if (month == 2) {
        // Leap year check
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (day > (isLeapYear ? 29 : 28)) return false;
    }

    return true;
}

bool BitcoinExchange::isValidValue(const float value) const {
    return (value >= 0 && value <= 1000);
}

// Custom exceptions
const char *BitcoinExchange::FileOpenException::what() const throw() {
    return "Error: could not open file.";
}