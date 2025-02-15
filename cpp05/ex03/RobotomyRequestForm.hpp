#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>	// rand()
#include <ctime>	// time()

class RobotomyRequestForm : public AForm {
	private:
		const std::string _target;
	public:
		RobotomyRequestForm(const std::string &target);	// Constructor
		RobotomyRequestForm(const RobotomyRequestForm &other);	// Copy constructor
		RobotomyRequestForm &operator=(const RobotomyRequestForm &other);	// Assignment operator
		virtual ~RobotomyRequestForm();	// Destructor
		// Execute the form
		void execute(const Bureaucrat &executor) const;
		// Grades required
		static const int signGrade = 72;
		static const int execGrade = 45;
};

#endif