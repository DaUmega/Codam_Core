#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP
# include <iostream>
# include <string>

class Zombie
{
public:
	Zombie(std::string name);
	~Zombie(void);
	void	Announce(void);
private:
	std::string	name;
};

Zombie*	newZombie(std::string input);
void	randomChump(std::string input);

#endif
