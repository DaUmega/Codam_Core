#include "Brain.hpp"

Brain::Brain(void)
{
	std::cout << "Brain constructor called.\n";
}

Brain::~Brain(void)
{
	std::cout << "Brain destructor called.\n";
}

Brain::Brain(Brain const &other)
{
	*this = other;
}

Brain &Brain::operator=(Brain const &other)
{
	for (int i = 0; i < 100; i++)
		this->ideas[i] = other.ideas[i];
	return (*this);
}
