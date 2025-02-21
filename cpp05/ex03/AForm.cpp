#include "AForm.hpp"

// Canonical Form
// Default constructor
AForm::AForm() : _name("default"), _gradeRequiredToSign(1), _gradeRequiredToExecute(1), _signed(false) {
}

// Default constructor
AForm::AForm(std::string name, int gradeRequiredToSign, int gradeRequiredToExecute) : _name(name), _gradeRequiredToSign(gradeRequiredToSign), _gradeRequiredToExecute(gradeRequiredToExecute), _signed(false) {
	validateGrades(gradeRequiredToSign, gradeRequiredToExecute);
}
// Copy constructor
AForm::AForm(const AForm &other) : _name(other._name), _gradeRequiredToSign(other._gradeRequiredToSign), _gradeRequiredToExecute(other._gradeRequiredToExecute), _signed(other._signed) {
}
// Assignation operator
AForm& AForm::operator=(const AForm &other) {
	if (this == &other) {
		return *this;
	}
	_signed = other._signed;
	return *this;
}
// Destructor
AForm::~AForm() {
}

// Protected member functions
void AForm::checkExecution(const Bureaucrat &executor) const {
	if (!_signed) {
		throw FormNotSignedException();
	}
	if (executor.getGrade() > _gradeRequiredToExecute) {
		throw GradeTooLowException();
	}
}

// Member functions
void AForm::beSigned(const Bureaucrat &bureaucrat) {
	if (_signed) {
		throw FormAlreadySignedException();
	}
	if (bureaucrat.getGrade() > _gradeRequiredToSign) {
		throw GradeTooLowException();
	}
	std::cout << bureaucrat.getName() << " signs " << _name << std::endl;
	_signed = true;
}

void AForm::validateGrades(int gradeToSign, int gradeToExecute) const {
	if (gradeToSign < 1 || gradeToExecute < 1) {
		throw GradeTooHighException();
	}
	if (gradeToSign > 150 || gradeToExecute > 150) {
		throw GradeTooLowException();
	}
}

// Getters
std::string AForm::getName() const {
	return _name;
}
bool AForm::getSigned() const {
	return _signed;
}
int AForm::getGradeRequiredToSign() const {
	return _gradeRequiredToSign;
}
int AForm::getGradeRequiredToExecute() const {
	return _gradeRequiredToExecute;
}

// Exceptions
const char* AForm::GradeTooHighException::what() const throw() {
    return "Grade is too high";
}
const char* AForm::GradeTooLowException::what() const throw() {
    return "Grade is too low";
}
const char* AForm::FormAlreadySignedException::what() const throw() {
	return "Form is already signed";
}
const char* AForm::FormNotSignedException::what() const throw() {
	return "Form is not signed";
}

std::ostream& operator<<(std::ostream &out, const AForm &form) {
	out << "Form: " << form.getName()
		<< "\nSigned: " << form.getSigned()
		<< "\nGrade required to sign: " << form.getGradeRequiredToSign()
		<< "\nGrade required to execute: " << form.getGradeRequiredToExecute();
	return out;
}
