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
	t_form	types[3] = {{"shrubbery", 0}, {"robotomy", 1}, {"presidential", 2}};
	
	int i;

	for (i = 0; i < 3; i++)
	{
		if (input.find(types[i]._t) < input.length())
			break;
	}
	
	switch (i)
	{
		case 0:
			std::cout << "Intern creates " << input << "\n";
			return (new ShrubberyCreationForm(name));
		case 1:
			std::cout << "Intern creates " << input << "\n";
			return (new RobotomyRequestForm(name));
		case 2:
			std::cout << "Intern creates " << input << "\n";
			return (new PresidentialPardonForm(name));
		default:
			throw(FormNotFoundException());
	}
}
