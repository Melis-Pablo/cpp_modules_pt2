#include "ShrubberyCreationForm.hpp"

// Constructor
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target) : AForm("ShrubberyCreationForm", signGrade, execGrade), _target(target){
}

// Copy constructor
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other), _target(other._target){
}

// Assignment operator
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
	if (this != &other){
		AForm::operator=(other);
	}
	return *this;
}

// Destructor
ShrubberyCreationForm::~ShrubberyCreationForm(){
}

// Execute the form
void ShrubberyCreationForm::execute(const Bureaucrat &executor) const {
	checkExecution(executor);

	// Create and open the file
	std::ofstream outFile((_target + "_shrubbery").c_str());

	// Check if the file is open
	if (!outFile.is_open()){
		throw std::runtime_error("Error: could not open file");
	}

	// Draw the tree
    outFile << "                                  " << std::endl;
    outFile << "              ,@@@@@@@,          " << std::endl;
    outFile << "      ,,,.   ,@@@@@@/@@,  .oo8888o." << std::endl;
    outFile << "   ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o" << std::endl;
    outFile << "  ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'" << std::endl;
    outFile << "  %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'" << std::endl;
    outFile << "  %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'" << std::endl;
    outFile << "  `&%\\ ` /%&'    |.|        \\ '|8'" << std::endl;
    outFile << "      |o|        | |         | |" << std::endl;
    outFile << "      |.|        | |         | |" << std::endl;
    outFile << "   \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_" << std::endl;
    outFile << std::endl;
    outFile << "         = Enchanted Forest =" << std::endl;

	// Close the file
	outFile.close();
}