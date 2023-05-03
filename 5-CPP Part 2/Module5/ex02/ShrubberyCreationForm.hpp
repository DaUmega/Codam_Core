#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP
# include "Bureaucrat.hpp"
# include "AForm.hpp"

class ShrubberyCreationForm: public AForm
{
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(std::string target);
	~ShrubberyCreationForm();
	ShrubberyCreationForm(const ShrubberyCreationForm &other);
	ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
	
	int			getExecGrade(void) const;
	int			getSignGrade(void) const;
	std::string	getName(void) const;
	bool		getSigned(void) const;
	
	void		action(void) const;
};

std::ostream &operator<<(std::ostream &out, ShrubberyCreationForm const &other);

#endif
