#include "ScalarConverter.hpp"
#include <climits>
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <cfloat>

// Private Canonical Form
ScalarConverter::ScalarConverter() {} // Default constructor
ScalarConverter::ScalarConverter(ScalarConverter const & other) { *this = other; } // Copy constructor
ScalarConverter& ScalarConverter::operator=(ScalarConverter const& other) {
	if (this != &other)
		*this = other;
	return *this;
} // Assignment operator
ScalarConverter::~ScalarConverter() {} // Destructor

// Helper type detection functions
bool ScalarConverter::isChar(const std::string& literal) {
	return (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'');
}

bool ScalarConverter::isInt(const std::string& literal) {
	size_t i = 0;
	if (literal[i] == '+' || literal[i] == '-')
		i++;
	if (i == literal.length())
		return false;
	while (i < literal.length()) {
		if (literal[i] < '0' || literal[i] > '9')
			return false;
		i++;
	}
	return true;
}

bool ScalarConverter::isFloat(const std::string& literal) {
	// Check for special cases
	if (literal == "nanf" || literal == "+inff" || literal == "-inff")
		return true;
	// Check for f suffix
	if (literal[literal.length() - 1] != 'f')
		return false;
	size_t i = 0;
	// Check for sign
	if (literal[i] == '+' || literal[i] == '-')
		i++;
	// Check for digits
	if (i == literal.length() - 1) // Only the sign
		return false;
	bool dot = false;
	bool numBeforeDot = false;
	bool numAfterDot = false;
	while (i < literal.length() - 1) {
		if (literal[i] == '.') {
			if (dot)
				return false;
			dot = true;
		}
		else if (literal[i] >='0' && literal[i] <='9') {
			if (dot)
				numAfterDot = true;
			else
				numBeforeDot = true;
		}
		else
			return false;
		i++;
	}
	return numBeforeDot && (!dot || numAfterDot);
}

bool ScalarConverter::isDouble(const std::string& literal) {
	// Check for special cases
	if (literal == "nan" || literal == "+inf" || literal == "-inf")
		return true;
	size_t i = 0;
	// Check for sign
	if (literal[i] == '+' || literal[i] == '-')
		i++;
	// Check for digits
	if (i == literal.length()) // Only the sign
		return false;
	bool dot = false;
	bool numBeforeDot = false;
	bool numAfterDot = false;
	while (i < literal.length()) {
		if (literal[i] == '.') {
			if (dot)
				return false;
			dot = true;
		}
		else if (literal[i] >='0' && literal[i] <='9') {
			if (dot)
				numAfterDot = true;
			else
				numBeforeDot = true;
		}
		else
			return false;
		i++;
	}
	return numBeforeDot && (!dot || numAfterDot);
}

// Helper conversion functions
void ScalarConverter::convertChar(const std::string& literal) {
	char c = literal[1];
	std::cout << "char: ";
	if (c < 32 || c > 126)
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

void ScalarConverter::convertInt(const std::string& literal) {
	double d = atof(literal.c_str()); //std::stod
	std::cout << "char: ";
	if (d < 32 || d > 126 || d != static_cast<int>(d))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(d) << "'" << std::endl;

	std::cout << "int: ";
	if (d < INT_MIN|| d > INT_MAX)
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(d) << std::endl;
	std::cout << "float: " << static_cast<float>(d) << ".0f" << std::endl;
	std::cout << "double: " << d << ".0" << std::endl;
}

void ScalarConverter::convertFloat(const std::string& literal) {
	if (literal == "nanf") {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return;
	}
	if (literal == "+inff" || literal == "-inff") {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << literal << std::endl;
		std::cout << "double: " << (literal[0] == '+' ? '+' : '-') << "inf" << std::endl;
		return;
	}
	double d = atof(literal.c_str()); //std::stod
	std::cout << "char: ";
	if (d < 32 || d > 126 || d != static_cast<int>(d))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(d) << "'" << std::endl;

	std::cout << "int: ";
	if (d < INT_MIN|| d > INT_MAX)
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(d) << std::endl;

	std::cout << "float: ";
	if (d < -FLT_MAX || d > FLT_MAX)
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<float>(d) << (d == static_cast<int>(d) ? ".0" : "") << "f" << std::endl;
	std::cout << "double: " << d << (d == static_cast<int>(d) ? ".0" : "") << std::endl;
}

void ScalarConverter::convertDouble(const std::string& literal) {
	if (literal == "nan") {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
		return;
	}
	if (literal == "+inf" || literal == "-inf") {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << (literal[0] == '+' ? "+inff" : "-inff") << std::endl;
		std::cout << "double: " << literal << std::endl;
		return;
	}
	double d = atof(literal.c_str()); //std::stod
	std::cout << "char: ";
	if (d < 32 || d > 126 || d != static_cast<int>(d))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(d) << "'" << std::endl;

	std::cout << "int: ";
	if (d < INT_MIN|| d > INT_MAX)
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(d) << std::endl;

	std::cout << "float: ";
	if (d < -FLT_MAX || d > FLT_MAX)
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<float>(d) << (d == static_cast<int>(d) ? ".0" : "") << "f" << std::endl;

	std::cout << "double: " << d << (d == static_cast<int>(d) ? ".0" : "") << std::endl;
}


// Main conversion
void ScalarConverter::convert(const std::string& literal) {
	if (literal.empty()) {
		std::cout << "Error: Empty input" << std::endl;
		return;
	}
	if (isChar(literal))
		convertChar(literal);
	else if (isFloat(literal))
		convertFloat(literal);
	else if (isDouble(literal))
		convertDouble(literal);
	else if (isInt(literal))
		convertInt(literal);
	else {
		std::cout << "Error: Invalid input" << std::endl;
		return;
	}
}