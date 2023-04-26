#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP
# include <iostream>

class ClapTrap
{
public:
	ClapTrap();
	ClapTrap(std::string const input);
	~ClapTrap();
	ClapTrap(const ClapTrap &input);
	ClapTrap &operator=(const ClapTrap &input);
	
	void	attack(const std::string &target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
private:
	std::string	_name;
	int			_hp;
	int			_ep;
	int			_dmg;
};

#endif
