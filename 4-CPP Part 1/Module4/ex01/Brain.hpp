#ifndef BRAIN_HPP
# define BRAIN_HPP
# include <iostream>

class Brain
{
public:
	Brain();
	virtual ~Brain();
	Brain(const Brain &other);
	Brain &operator=(const Brain &other);
protected:
	std::string	ideas[100];
};

#endif
