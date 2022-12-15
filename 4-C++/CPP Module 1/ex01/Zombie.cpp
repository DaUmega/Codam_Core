#include "Zombie.hpp"

Zombie::Zombie(std::string input)
{
	this->name = input;
	std::cout << this->name << " has been created!\n";
}

Zombie::Zombie(void) {}

Zombie::~Zombie(void)
{
	std::cout << this->name << " has been destroyed!\n";
}

void	Zombie::Announce(void)
{
	std::cout << this->name << " BraiiiiiiinnnzzzZ...\n";
}

void	Zombie::SetName(std::string input)
{
	this->name = input;
	std::cout << this->name << " has been created!\n";
}
