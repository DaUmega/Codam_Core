#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP
# include <iostream>

class ClapTrap
{
public:
	ClapTrap();
	ClapTrap(std::string const input);
	~ClapTrap();
	
	void		attack(const std::string &target);
	void		takeDamage(unsigned int amount);
	void		beRepaired(unsigned int amount);
	std::string	getName(void);
	int			getDMG(void);
private:
	std::string	_name;
	int			_hp;
	int			_ep;
	int			_dmg;
};

#endif
