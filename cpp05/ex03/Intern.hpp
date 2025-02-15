#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>
#include <exception>
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern {
	public:
		Intern();	 // Default constructor
		Intern(Intern const & src);	// Copy constructor
		Intern & operator=(Intern const & src);	// Assignation operator
		~Intern();	// Destructor

		AForm * makeForm(std::string formName, std::string target);

		class FormNotFoundException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
};

#endif