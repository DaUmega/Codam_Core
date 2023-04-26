#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void)
{
	_name = "Scav";
	_hp = 100;
	_ep = 50;
	_dmg = 20;
	std::cout << "ScavTrap constructor called.\n";
}

ScavTrap::ScavTrap(std::string const input)
{
	_name = input;
	_hp = 100;
	_ep = 50;
	_dmg = 20;
	std::cout << _name << " (ScavTrap) has been created.\n";
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap destructor called.\n";
}

ScavTrap::ScavTrap(ScavTrap const &other)
{
	_name = other._name;
	_hp = other._hp;
	_ep = other._ep;
	_dmg = other._dmg;
}

ScavTrap &ScavTrap::operator=(ScavTrap const &other)
{
	this->_name = other._name;
	this->_hp = other._hp;
	this->_ep = other._ep;
	this->_dmg = other._dmg;
	return (*this);
}

void	ScavTrap::attack(const std::string &target)
{
	if (_hp > 0)
	{
		std::cout	<< "ScavTrap " << _name << " attacks " << target 
					<< ", causing " << _dmg << " points of damage!\n";
		_ep--;
		std::cout	<< _name << " stats: HP " << _hp << ", EP " << _ep << "\n";
	}
	else
		std::cout << "ScavTrap " << _name << " is dead!\n";
}

std::string	ScavTrap::getName(void)
{
	return _name;
}

int	ScavTrap::getDMG(void)
{
	return _dmg;
}

void	ScavTrap::guardGate(void)
{
	std::cout << "ScavTrap " << _name << " is now in Gate Keeper Mode!\n";
}
