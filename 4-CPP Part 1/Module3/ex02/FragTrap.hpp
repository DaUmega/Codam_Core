#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP
# include <iostream>
# include "ClapTrap.hpp"

class FragTrap: public ClapTrap
{
public:
	FragTrap();
	FragTrap(std::string const input);
	~FragTrap();
	FragTrap(const ClapTrap &other);
	FragTrap &operator=(const ClapTrap &other);
	
	void		attack(const std::string &target);
	void		takeDamage(unsigned int amount);
	void		beRepaired(unsigned int amount);
	std::string	getName(void);
	int			getDMG(void);
	void		highFivesGuys(void);
private:
	std::string	_name;
	int			_hp;
	int			_ep;
	int			_dmg;
};

#endif
