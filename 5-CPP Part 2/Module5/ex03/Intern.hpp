#ifndef INTERN_HPP
# define INTERN_HPP
# include <iostream>
# include <stdexcept>

class AForm;

class Intern
{
public:
	Intern();
	~Intern();
	Intern(const Intern &other);
	Intern &operator=(const Intern &other);
	
	AForm	*makeForm(std::string input, std::string name);

	class	FormNotFoundException: public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
};

#endif
