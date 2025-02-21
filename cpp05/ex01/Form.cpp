#include "Form.hpp"

// Canonical Form
// Default constructor
Form::Form() : _name("default"), _gradeRequiredToSign(1), _gradeRequiredToExecute(1), _signed(false) {
}

// Default constructor
Form::Form(std::string name, int gradeRequiredToSign, int gradeRequiredToExecute) : _name(name), _gradeRequiredToSign(gradeRequiredToSign), _gradeRequiredToExecute(gradeRequiredToExecute), _signed(false) {
	validateGrades(gradeRequiredToSign, gradeRequiredToExecute);
}
// Copy constructor
Form::Form(const Form &other) : _name(other._name), _gradeRequiredToSign(other._gradeRequiredToSign), _gradeRequiredToExecute(other._gradeRequiredToExecute), _signed(other._signed) {
}
// Assignation operator
Form& Form::operator=(const Form &other) {
	if (this == &other) {
		return *this;
	}
	_signed = other._signed;
	return *this;
}
// Destructor
Form::~Form() {
}
// Member functions
void Form::beSigned(const Bureaucrat &bureaucrat) {
	if (_signed) {
		throw FormAlreadySignedException();
	}
	if (bureaucrat.getGrade() > _gradeRequiredToSign) {
		throw GradeTooLowException();
	}
	_signed = true;
}

void Form::validateGrades(int gradeToSign, int gradeToExecute) const {
	if (gradeToSign < 1 || gradeToExecute < 1) {
		throw GradeTooHighException();
	}
	if (gradeToSign > 150 || gradeToExecute > 150) {
		throw GradeTooLowException();
	}
}

// Getters
std::string Form::getName() const {
	return _name;
}
bool Form::getSigned() const {
	return _signed;
}
int Form::getGradeRequiredToSign() const {
	return _gradeRequiredToSign;
}
int Form::getGradeRequiredToExecute() const {
	return _gradeRequiredToExecute;
}

// Exceptions
const char* Form::GradeTooHighException::what() const throw() {
    return "Grade is too high";
}
const char* Form::GradeTooLowException::what() const throw() {
    return "Grade is too low";
}
const char* Form::FormAlreadySignedException::what() const throw() {
	return "Form is already signed";
}

std::ostream& operator<<(std::ostream &out, const Form &form) {
	out << "Form: " << form.getName()
		<< "\nSigned: " << form.getSigned()
		<< "\nGrade required to sign: " << form.getGradeRequiredToSign()
		<< "\nGrade required to execute: " << form.getGradeRequiredToExecute();
	return out;
}
