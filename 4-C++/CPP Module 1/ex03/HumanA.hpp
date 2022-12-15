#ifndef	HUMANA_HPP
# define HUMANA_HPP
# include <string>
# include "Weapon.hpp"

class HumanA
{
public:
	~HumanA(void);
	HumanA(std::string input, Weapon &temp);
	void		attack(void);
	void		setWeapon(Weapon temp);

private:
	Weapon		&weapon;
	std::string	name;
};

#endif
