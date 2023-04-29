#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP
# include <iostream>
# include "Brain.hpp"

class WrongAnimal
{
public:
	WrongAnimal();
	virtual ~WrongAnimal();
	WrongAnimal(const WrongAnimal &other);
	WrongAnimal &operator=(const WrongAnimal &other);
	
	void		makeSound(void) const;
	std::string	getType(void) const;
protected:
	std::string	type;
	Brain		*brain;
};

#endif
