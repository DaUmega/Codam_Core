#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void): _name("Default"), _hp(100), _ep(50), _dmg(20)
{
	std::cout << "ScavTrap constructor called.\n";
}

ScavTrap::ScavTrap(std::string const input): _name(input), _hp(100), _ep(50), _dmg(20)
{
	std::cout << _name << " (ScavTrap) has been created.\n";
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap destructor called.\n";
}

void	ScavTrap::attack(const std::string &target)
{
	if (_hp > 0)
	{
		std::cout	<< "ScavTrap " << _name << " attacks " << target 
					<< ", causing " << _dmg << " points of damage!\n";
		std::cout	<< _name << " stats: HP " << _hp << ", EP " << _ep << "\n";
	}
	else
		std::cout << "ScavTrap " << _name << " is dead!\n";
}
void	ScavTrap::takeDamage(unsigned int amount)
{
	if (_hp > 0)
	{
		std::cout	<< "ScavTrap " << _name << " receives " << amount << " points of damage!\n";
		_hp -= amount;
		std::cout	<< _name << " stats: HP " << _hp << ", EP " << _ep << "\n";
	}
	else
		std::cout << "ScavTrap " << _name << " is dead!\n";
}
void	ScavTrap::beRepaired(unsigned int amount)
{
	if (_hp > 0 && _ep > 0)
	{
		std::cout	<< "ScavTrap " << _name << " recovers " << amount 
					<< " HitPoints and loses 1 Energy Point!\n";
		_hp += amount;
		_ep--;
		std::cout	<< _name << " stats: HP " << _hp << ", EP " << _ep << "\n";
	}
	else if (_hp > 0 && _ep <= 0)
		std::cout << "ScavTrap " << _name << " has no Energy Points left!\n";
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
