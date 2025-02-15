#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>	// For file handling

class ShrubberyCreationForm : public AForm {
	private:
		const std::string _target;
	public:
		ShrubberyCreationForm(const std::string &target);	// Constructor
		ShrubberyCreationForm(const ShrubberyCreationForm &other);	// Copy constructor
		ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);	// Assignment operator
		virtual ~ShrubberyCreationForm();	// Destructor
		// Execute the form
		void execute(const Bureaucrat &executor) const;
		// Grades required
		static const int signGrade = 145;
		static const int execGrade = 137;
};

#endif