#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern(void)
{
	std::cout << "Intern constructor called.\n";
}

Intern::~Intern(void)
{
	std::cout << "Intern destructor called.\n";
}

Intern::Intern(Intern const &other)
{
	*this = other;
}

Intern &Intern::operator=(Intern const &other)
{
	(void)other;
	return *this;
}

const char* Intern::FormNotFoundException::what() const throw()
{
	return ("Form not found.\n");
}

AForm	*Intern::makeForm(std::string input, std::string name)
{
	if (input.find("shrubbery") < input.length())
	{
		std::cout << "Intern creates " << input << "\n";
		return (new ShrubberyCreationForm(name));
	}
	else if (input.find("robotomy") < input.length())
	{
		std::cout << "Intern creates " << input << "\n";
		return (new RobotomyRequestForm(name));
	}
	else if (input.find("presidential") < input.length())
	{
		std::cout << "Intern creates " << input << "\n";
		return (new PresidentialPardonForm(name));
	}
	else
		throw(FormNotFoundException());
}
