#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap a;
	ClapTrap b("AAAAHHHHH");

	a.attack("some guy");
	b.attack("some guy");
	a.takeDamage(4);
	b.takeDamage(4);
	a.beRepaired(4);
	b.beRepaired(4);
	a.takeDamage(40);
	b.takeDamage(40);
	a.beRepaired(4);
	b.beRepaired(4);
}
