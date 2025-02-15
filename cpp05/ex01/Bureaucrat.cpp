#include "Bureaucrat.hpp"
#include "Form.hpp"

// Canonical Form
// Default Constructor with parameters (Must have a name and a grade)
Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
	validateGrade(grade);
	_grade = grade;
}

// Copy Constructor
Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other._name), _grade(other._grade) {
}

// Assignment Operator
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
	if (this != &other) {
		_grade = other._grade;
	}
	return *this;
}

// Destructor
Bureaucrat::~Bureaucrat(){
}

// Member Functions
void Bureaucrat::signForm(Form& form) {
	if (_grade > form.getGradeRequiredToSign()) {
		throw GradeTooLowException();
	}
	form.beSigned(*this);
}

// Getters
std::string Bureaucrat::getName() const {
	return _name;
}

int Bureaucrat::getGrade() const {
	return _grade;
}

// check for invalid grade
void Bureaucrat::validateGrade(int grade) const {
	if (grade < 1) {
		throw GradeTooHighException();
	} else if (grade > 150) {
		throw GradeTooLowException();
	}
}

// Grade Increment/Decrement
void Bureaucrat::incrementGrade(void) {
	validateGrade(_grade -1);
	_grade--;
}
void Bureaucrat::decrementGrade(void) {
	validateGrade(_grade +1);
	_grade++;
}

// Exception Classes
const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return "Grade is too high";
}
const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return "Grade is too low";
}

// Insertion (<<) Operator Overload
std::ostream& operator<<(std::ostream& out, const Bureaucrat& Bureaucrat) {
	out << Bureaucrat.getName() << ", bureaucrat grade " << Bureaucrat.getGrade() << std::endl;
	return out;
}
