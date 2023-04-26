#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int	main(void)
{
	ClapTrap a("AAAAHHHHH");
	FragTrap b("Big dude");

	a.attack(b.getName());
	b.takeDamage(a.getDMG());
	b.attack(a.getName());
	a.takeDamage(b.getDMG());
	a.beRepaired(4);
	b.beRepaired(4);
	b.highFivesGuys();
}
