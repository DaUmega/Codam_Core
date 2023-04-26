#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP
# include <iostream>
# include "ClapTrap.hpp"

class ScavTrap: public ClapTrap
{
public:
	ScavTrap();
	ScavTrap(std::string const input);
	~ScavTrap();
	ScavTrap(const ClapTrap &other);
	ScavTrap &operator=(const ClapTrap &other);
	
	void		attack(const std::string &target);
	void		takeDamage(unsigned int amount);
	void		beRepaired(unsigned int amount);
	std::string	getName(void);
	int			getDMG(void);
	void		guardGate(void);
private:
	std::string	_name;
	int			_hp;
	int			_ep;
	int			_dmg;
};

#endif
