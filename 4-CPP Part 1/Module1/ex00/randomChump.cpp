#include "Zombie.hpp"

void	randomChump(std::string input)
{
	Zombie	temp = Zombie(input);
	temp.Announce();
}
