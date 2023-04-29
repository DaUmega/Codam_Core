#include "Dog.hpp"

Dog::Dog(void)
{
	type = "Dog";
	std::cout << "Dog constructor called.\n";
	brain = new Brain();
}

Dog::~Dog(void)
{
	delete brain;
	std::cout << "Dog destructor called.\n";
}

Dog::Dog(Dog const &other)
{
	*this = other;
}

Dog &Dog::operator=(Dog const &other)
{
	this->type = other.type;
	this->brain = new Brain(*other.brain);
	return (*this);
}
