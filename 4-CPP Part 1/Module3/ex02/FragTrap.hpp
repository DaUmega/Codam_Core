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
	FragTrap(const FragTrap &other);
	FragTrap &operator=(const FragTrap &other);
	
	void		attack(const std::string &target);
	std::string	getName(void);
	int			getDMG(void);
	void		highFivesGuys(void);
};

#endif
