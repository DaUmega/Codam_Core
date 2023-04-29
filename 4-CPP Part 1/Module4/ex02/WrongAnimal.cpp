#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void): type("WrongAnimal")
{
	std::cout << "WrongAnimal constructor called.\n";
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "WrongAnimal destructor called.\n";
}

WrongAnimal::WrongAnimal(WrongAnimal const &other): type(other.type)
{}

WrongAnimal &WrongAnimal::operator=(WrongAnimal const &other)
{
	this->type = other.type;
	return (*this);
}

void	WrongAnimal::makeSound(void) const
{
	std::cout << "Realistic WrongAnimal sounds.\n";
}

std::string	WrongAnimal::getType(void) const
{
	return type;
}