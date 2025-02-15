#ifndef FORM_HPP
#define FORM_HPP

#include <iostream> 	// ostream
#include <string>		// string
#include <exception>	// exception
#include "Bureaucrat.hpp"

class Form {
	private:
		const std::string _name;
		const int _gradeRequiredToSign;
		const int _gradeRequiredToExecute;
		bool _signed;
		void validateGrades(int gradeToSign, int gradeToExecute) const;
	public:
	// Canonical Form
		Form(std::string name, int gradeRequiredToSign, int gradeRequiredToExecute);	// Default Constructor with parameters
		Form(const Form &other);	// Copy Constructor
		Form &operator=(const Form &other);	// Assignation operator
		~Form();	// Destructor
	// Member functions
		void beSigned(const Bureaucrat &bureaucrat);
		// Getters
		std::string getName() const;
	 	bool getSigned() const;
		int getGradeRequiredToSign() const;
		int getGradeRequiredToExecute() const;
	// Exception Classes
		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class FormAlreadySignedException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

// Insertion (<<) Operator Overload
std::ostream &operator<<(std::ostream &out, const Form &form);

#endif