#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream> 	// ostream
#include <string>		// string
#include <exception>	// exception
#include "Bureaucrat.hpp"

class AForm {
	private:
		const std::string _name;
		const int _gradeRequiredToSign;
		const int _gradeRequiredToExecute;
		bool _signed;
		void validateGrades(int gradeToSign, int gradeToExecute) const;
	protected:
		void checkExecution(const Bureaucrat &executor) const;
	public:
	// Canonical Form
		AForm(std::string name, int gradeRequiredToSign, int gradeRequiredToExecute);	// Default Constructor with parameters
		AForm(const AForm &other);	// Copy Constructor
		AForm &operator=(const AForm &other);	// Assignation operator
		virtual ~AForm();	// Destructor
	// Member functions
		void beSigned(const Bureaucrat &bureaucrat);
		virtual void execute(const Bureaucrat &executor) const = 0;
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
		class FormNotSignedException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

// Insertion (<<) Operator Overload
std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif