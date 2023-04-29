#include "WrongCat.hpp"

WrongCat::WrongCat(void)
{
	type = "WrongCat";
	std::cout << "WrongCat constructor called.\n";
}

WrongCat::~WrongCat(void)
{
	std::cout << "WrongCat destructor called.\n";
}

WrongCat::WrongCat(WrongCat const &other)
{
	type = other.type;
}

WrongCat &WrongCat::operator=(WrongCat const &other)
{
	this->type = other.type;
	return (*this);
}
