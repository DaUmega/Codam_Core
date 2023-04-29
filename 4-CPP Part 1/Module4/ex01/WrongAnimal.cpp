#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void): type("WrongAnimal")
{
	brain = new Brain();
	std::cout << "WrongAnimal constructor called.\n";
}

WrongAnimal::~WrongAnimal(void)
{
	delete brain;
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
	std::cout << "Realistic " << type << " sounds.\n";
}

std::string	WrongAnimal::getType(void) const
{
	return type;
}