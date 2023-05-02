#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void): type("Bureaucrat")
{
	std::cout << "Bureaucrat constructor called.\n";
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << "Bureaucrat destructor called.\n";
}

Bureaucrat::Bureaucrat(Bureaucrat const &other): type(other.type)
{}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &other)
{
	this->type = other.type;
	return (*this);
}

void	Bureaucrat::makeSound(void) const
{
	std::cout << "Realistic " << type << " sounds.\n";
}

std::string	Bureaucrat::getType(void) const
{
	return type;
}
