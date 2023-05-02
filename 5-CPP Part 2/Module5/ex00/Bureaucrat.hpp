#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP
# include <iostream>

class Bureaucrat
{
public:
	Bureaucrat();
	virtual ~Bureaucrat();
	Bureaucrat(const Bureaucrat &other);
	Bureaucrat &operator=(const Bureaucrat &other);
	
	void		makeSound(void) const;
	std::string	getType(void) const;
protected:
	std::string	type;
};

#endif
