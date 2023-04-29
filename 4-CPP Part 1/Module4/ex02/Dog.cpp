#include "Dog.hpp"

Dog::Dog(void)
{
	type = "Dog";
	std::cout << "Dog constructor called.\n";
}

Dog::~Dog(void)
{
	std::cout << "Dog destructor called.\n";
}

Dog::Dog(Dog const &other)
{
	type = other.type;
}

Dog &Dog::operator=(Dog const &other)
{
	this->type = other.type;
	return (*this);
}
