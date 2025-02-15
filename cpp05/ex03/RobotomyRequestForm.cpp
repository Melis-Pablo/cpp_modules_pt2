#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

// Constructor
RobotomyRequestForm::RobotomyRequestForm(const std::string &target) : AForm("RobotomyRequestForm", signGrade, execGrade), _target(target){
}

// Copy constructor
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) : AForm(other), _target(other._target){
}

// Assignment operator
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
	if (this != &other){
		AForm::operator=(other);
	}
	return *this;
}

// Destructor
RobotomyRequestForm::~RobotomyRequestForm(){
}

// Execute the form
void RobotomyRequestForm::execute(const Bureaucrat &executor) const {
	AForm::checkExecution(executor);
	std::cout << "* Drilling noises *" << std::endl;
	std::srand(std::time(NULL));
	if (rand() % 2) {
		std::cout << _target << " has been robotomized successfully" << std::endl;
	}
	else {
		std::cout << _target << " robotomization failed" << std::endl;
	}
}