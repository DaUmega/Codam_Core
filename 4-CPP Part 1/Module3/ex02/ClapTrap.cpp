#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void): _name("Default"), _hp(10), _ep(10), _dmg(0)
{
	std::cout << "Default constructor called.\n";
}

ClapTrap::ClapTrap(std::string const input): _name(input), _hp(10), _ep(10), _dmg(0)
{
	std::cout << _name << " has been created.\n";
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "Default destructor called.\n";
}

ClapTrap::ClapTrap(ClapTrap const &other): _name(other._name), 
	_hp(other._hp), _ep(other._ep), _dmg(other._dmg)
{}

ClapTrap &ClapTrap::operator=(ClapTrap const &other)
{
	this->_name = other._name;
	this->_hp = other._hp;
	this->_ep = other._ep;
	this->_dmg = other._dmg;
	return (*this);
}

void	ClapTrap::attack(const std::string &target)
{
	if (_hp > 0)
	{
		std::cout	<< "ClapTrap " << _name << " attacks " << target 
					<< ", causing " << _dmg << " points of damage!\n";
		_ep--;
		std::cout	<< _name << " stats: HP " << _hp << ", EP " << _ep << "\n";
	}
	else
		std::cout << "ClapTrap " << _name << " is dead!\n";
}
void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hp > 0)
	{
		std::cout	<< "ClapTrap " << _name << " receives " << amount << " points of damage!\n";
		_hp -= amount;
		std::cout	<< _name << " stats: HP " << _hp << ", EP " << _ep << "\n";
	}
	else
		std::cout << "ClapTrap " << _name << " is dead!\n";
}
void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hp > 0 && _ep > 0)
	{
		std::cout	<< "ClapTrap " << _name << " recovers " << amount 
					<< " HitPoints and loses 1 Energy Point!\n";
		_hp += amount;
		_ep--;
		std::cout	<< _name << " stats: HP " << _hp << ", EP " << _ep << "\n";
	}
	else if (_hp > 0 && _ep <= 0)
		std::cout << "ClapTrap " << _name << " has no Energy Points left!\n";
	else
		std::cout << "ClapTrap " << _name << " is dead!\n";
}

std::string	ClapTrap::getName(void)
{
	return _name;
}

int	ClapTrap::getDMG(void)
{
	return _dmg;
}
