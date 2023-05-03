#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void): AForm("ShrubberyCreationForm", 145, 137)
{
	_target = "Default";
	std::cout << "ShrubberyCreationForm constructor called.\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("ShrubberyCreationForm", 145, 137)
{
	_target = target;
	std::cout << "ShrubberyCreationForm created with target: " << _target << "\n";
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	std::cout << "ShrubberyCreationForm destructor called.\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other): AForm(other)
{
	_target = other._target;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &other)
{
	if (this != &other)
		_target = other._target;
	return *this;
}

void	ShrubberyCreationForm::beSigned(Bureaucrat &input)
{
	if (input.getGrade() > _signGrade)
		throw ShrubberyCreationForm::GradeTooLowException();
	_signed = true;
	std::cout << input.getName() << " signed " << _name;
}

const char* ShrubberyCreationForm::GradeTooHighException::what() const throw()
{
	return ("Grade too HIGH!\n");
}

const char* ShrubberyCreationForm::GradeTooLowException::what() const throw()
{
	return ("Grade too LOW!\n");
}

std::ostream &operator<<(std::ostream &out, ShrubberyCreationForm const &other)
{
	out << "ShrubberyCreationForm name: " << other.getName()
	<< ", Sign Grade: " << other.getSignGrade()
	<< ", Grade to execute: " << other.getExecGrade()
	<< ", Signed: " << other.getSigned() << std::endl;
    return (out);
}
