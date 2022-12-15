#ifndef	HUMANB_HPP
# define HUMANB_HPP
# include <string>
# include "Weapon.hpp"

class HumanB
{
public:
	HumanB(std::string input);
	~HumanB(void);
	void		attack(void);
	void		setWeapon(Weapon &temp);

private:
	Weapon		*weapon;
	std::string	name;
};

#endif
