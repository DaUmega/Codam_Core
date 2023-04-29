#include "FragTrap.hpp"

FragTrap::FragTrap(void)
{
	_name = "Frag";
	_hp = 100;
	_ep = 100;
	_dmg = 30;
	std::cout << "FragTrap constructor called.\n";
}

FragTrap::FragTrap(std::string const input)
{
	_name = input;
	_hp = 100;
	_ep = 100;
	_dmg = 30;
	std::cout << _name << " (FragTrap) has been created.\n";
}

FragTrap::~FragTrap(void)
{
	std::cout << "FragTrap destructor called.\n";
}

FragTrap::FragTrap(FragTrap const &other)
{
	_name = other._name;
	_hp = other._hp;
	_ep = other._ep;
	_dmg = other._dmg;
}

FragTrap &FragTrap::operator=(FragTrap const &other)
{
	this->_name = other._name;
	this->_hp = other._hp;
	this->_ep = other._ep;
	this->_dmg = other._dmg;
	return (*this);
}

void	FragTrap::attack(const std::string &target)
{
	if (_hp > 0)
	{
		std::cout	<< "FragTrap " << _name << " attacks " << target 
					<< ", causing " << _dmg << " points of damage!\n";
		_ep--;
		std::cout	<< _name << " stats: HP " << _hp << ", EP " << _ep << "\n";
	}
	else
		std::cout << "FragTrap " << _name << " is dead!\n";
}

std::string	FragTrap::getName(void)
{
	return _name;
}

int	FragTrap::getDMG(void)
{
	return _dmg;
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << _name << " is high fiving everyone including the dead!\n";
}
