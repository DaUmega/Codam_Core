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
	type = other.type;
	brain = other.brain;
}

Cat &Cat::operator=(Cat const &other)
{
	this->type = other.type;
	this->brain = other.brain;
	return (*this);
}
