#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
	private:
		const std::string _target;
	public:
		PresidentialPardonForm(const std::string &target);	// Constructor
		PresidentialPardonForm(const PresidentialPardonForm &other);	// Copy constructor
		PresidentialPardonForm &operator=(const PresidentialPardonForm &other);	// Assignment operator
		virtual ~PresidentialPardonForm();	// Destructor
		// Execute the form
		void execute(const Bureaucrat &executor) const;
		// Grades required
		static const int signGrade = 25;
		static const int execGrade = 5;
};

#endif