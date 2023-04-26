#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ClapTrap a("AAAAHHHHH");
	ScavTrap b("Big dude");

	a.attack(b.getName());
	b.takeDamage(a.getDMG());
	b.attack(a.getName());
	a.takeDamage(b.getDMG());
	a.beRepaired(4);
	b.beRepaired(4);
}
