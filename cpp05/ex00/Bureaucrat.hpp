#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream> 	// ostream
#include <string>		// string
#include <exception>	// exception

class Bureaucrat
{
	private:
		const std::string _name;
		int _grade; // 1-150
		void validateGrade(int grade) const;
	public:
	// Canonical Form
		Bureaucrat(const std::string& name, int grade);	// Default Constructor with parameters
		Bureaucrat(const Bureaucrat& other);	// Copy Constructor
		Bureaucrat& operator=(const Bureaucrat& other);	// Assignment Operator
		~Bureaucrat();	// Destructor
	// Member Functions
		// Getters
		std::string getName() const;
		int getGrade() const;
		// Grade Increment/Decrement
		void incrementGrade(void);
		void decrementGrade(void);
	// Exception Classes
	class GradeTooHighException : public std::exception {
		public:
			const char* what() const throw();
	};
	class GradeTooLowException : public std::exception {
		public:
			const char* what() const throw();
	};
};

// Insertion (<<) Operator Overload
std::ostream& operator<<(std::ostream& out, const Bureaucrat& Bureaucrat);

#endif