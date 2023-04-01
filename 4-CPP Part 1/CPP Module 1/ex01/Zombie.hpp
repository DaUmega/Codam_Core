#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP
# include <iostream>
# include <string>

class Zombie
{
public:
	Zombie(std::string name);
	Zombie(void);
	~Zombie(void);
	void	SetName(std::string input);
	void	Announce(void);
private:
	std::string	name;
};

Zombie*	newZombie(std::string input);
Zombie*	zombieHorde(int N, std::string name);

#endif
