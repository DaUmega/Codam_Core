#include "Cat.hpp"

Cat::Cat(void)
{
	type = "Cat";
	std::cout << "Cat constructor called.\n";
	brain = new Brain();
}

Cat::~Cat(void)
{
	delete brain;
	std::cout << "Cat destructor called.\n";
}

Cat::Cat(Cat const &other)
{
	*this = other;
}

Cat &Cat::operator=(Cat const &other)
{
	this->type = other.type;
	this->brain = new Brain(*other.brain);
	return (*this);
}
