#include "Weapon.hpp"

Weapon::Weapon(std::string input) 
{
	this->type = input;
}

Weapon::~Weapon(void) {}

const std::string Weapon::getType(void)
{
	return (this->type);
}

void	Weapon::setType(std::string input)
{
	this->type = input;
}
