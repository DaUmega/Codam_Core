#include "Zombie.hpp"

int	main(void)
{
	Zombie	*temp = zombieHorde(3, "Herp");

	for (int i = 0; i < 3; i++)
		temp[i].Announce();
	delete [] temp;
}
