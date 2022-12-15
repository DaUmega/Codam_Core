#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string input, Weapon &temp): weapon(temp)
{
	this->name = input;
	this->weapon = temp;
	std::cout << this->name << " has been created with weapon: " << this->weapon.getType();
}

HumanA::~HumanA(void)
{
	std::cout << this->name << " has been destroyed.\n";
}

void	HumanA::attack(void)
{
	std::cout << this->name << " attacks with their " << this->weapon.getType() << "\n";
}

void	HumanA::setWeapon(Weapon temp)
{
	this->weapon = temp;
}
