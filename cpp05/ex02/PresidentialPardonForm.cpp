#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) : AForm("PresidentialPardonForm", signGrade, execGrade), _target(target){
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) : AForm(other), _target(other._target){
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
	if (this != &other){
		AForm::operator=(other);
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm(){
}

// Execute the form
void PresidentialPardonForm::execute(const Bureaucrat &executor) const {
	AForm::checkExecution(executor);
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}