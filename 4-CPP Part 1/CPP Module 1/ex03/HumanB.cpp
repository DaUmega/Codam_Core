#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string input)
{
	this->name = input;
	std::cout << this->name << " has been created.\n";
}

HumanB::~HumanB(void)
{
	std::cout << this->name << " has been destroyed.\n";
}

void	HumanB::attack(void)
{
	std::cout << this->name << " attacks with their " << this->weapon->getType() << "\n";
}

void	HumanB::setWeapon(Weapon &temp)
{
	this->weapon = &temp;
}
