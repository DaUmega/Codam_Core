#include "Animal.hpp"

Animal::Animal(void): type("Animal")
{
	brain = new Brain();
	std::cout << "Animal constructor called.\n";
}

Animal::~Animal(void)
{
	delete brain;
	std::cout << "Animal destructor called.\n";
}

Animal::Animal(Animal const &other): type(other.type)
{}

Animal &Animal::operator=(Animal const &other)
{
	this->type = other.type;
	return (*this);
}

void	Animal::makeSound(void) const
{
	std::cout << "Realistic " << type << " sounds.\n";
}

std::string	Animal::getType(void) const
{
	return type;
}
