#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
	private:
		// Private Canonical Form
		ScalarConverter();	// Default constructor
		ScalarConverter(ScalarConverter const & other); // Copy constructor
		ScalarConverter& operator=(ScalarConverter const& other); // Assignment operator
		~ScalarConverter(); // Destructor

		// Helper type detection functions
		static bool isChar(const std::string& literal);
		static bool isInt(const std::string& literal);
		static bool isFloat(const std::string& literal);
		static bool isDouble(const std::string& literal);

		// Helper conversion functions
		static void convertChar(const std::string& literal);
		static void convertInt(const std::string& literal);
		static void convertFloat(const std::string& literal);
		static void convertDouble(const std::string& literal);

	public:
		static void convert(const std::string& literal);
};

#endif