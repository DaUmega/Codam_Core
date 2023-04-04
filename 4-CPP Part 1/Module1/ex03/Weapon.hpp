#ifndef	WEAPON_HPP
# define WEAPON_HPP
# include <string>

class Weapon
{
public:
	Weapon(std::string input);
	~Weapon(void);
	const std::string	getType(void);
	void				setType(std::string input);

private:
	std::string			type;
};

#endif
