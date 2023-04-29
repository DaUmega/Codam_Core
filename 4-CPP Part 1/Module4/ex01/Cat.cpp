#include "Cat.hpp"

Cat::Cat(void)
{
	type = "Cat";
	std::cout << "Cat constructor called.\n";
}

Cat::~Cat(void)
{
	std::cout << "Cat destructor called.\n";
}

Cat::Cat(Cat const &other)
{
	type = other.type;
}

Cat &Cat::operator=(Cat const &other)
{
	this->type = other.type;
	return (*this);
}
