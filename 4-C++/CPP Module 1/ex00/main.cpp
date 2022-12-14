#include "Zombie.hpp"

int	main(void)
{
	Zombie	*temp = newZombie("Herp");
	temp->Announce();
	randomChump("Derp");
	delete temp;
}
