#include "Zombie.hpp"

Zombie* newZombie(std::string input)
{
	return (new Zombie(input));
}
