#include "Intern.hpp"

// Default constructor
Intern::Intern() {
}
// Copy constructor
Intern::Intern(Intern const & src) {
	*this = src;
}
// Assignation operator
Intern & Intern::operator=(Intern const & src) {
	if (this != &src) {
		// No attributes to copy
	}
	return *this;
}
// Destructor
Intern::~Intern() {
}

// Class not found exception
const char * Intern::FormNotFoundException::what() const throw() {
	return "Form not found";
}

// Form creation functions
static AForm * createPresidentialPardonForm(const std::string target) {
	return new PresidentialPardonForm(target);
}

static AForm * createRobotomyRequestForm(const std::string target) {
	return new RobotomyRequestForm(target);
}

static AForm * createShrubberyCreationForm(const std::string target) {
	return new ShrubberyCreationForm(target);
}

// Form creation function
AForm * Intern::makeForm(std::string formName, std::string target) {
	struct FormType {
		std::string name;
		AForm * (*create)(std::string target);
	};

	static const FormType forms[3] = {
		{"presidential pardon", createPresidentialPardonForm},
		{"robotomy request", createRobotomyRequestForm},
		{"shrubbery creation", createShrubberyCreationForm}
	};

	static const int formsCount = 3;

	for (int i = 0; i < formsCount; i++) {
		if (forms[i].name == formName) {
			std::cout << "Intern creates " << formName << std::endl;
			return forms[i].create(target);
		}
	}

	throw FormNotFoundException();
}