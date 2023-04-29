#ifndef ANIMAL_HPP
# define ANIMAL_HPP
# include <iostream>
# include "Brain.hpp"

class Animal
{
public:
	virtual ~Animal();
	Animal(const Animal &other);
	Animal &operator=(const Animal &other);
	
	void		makeSound(void) const;
	std::string	getType(void) const;
protected:
	Animal();
	std::string	type;
	Brain		*brain;
};

#endif
