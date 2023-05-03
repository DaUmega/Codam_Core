#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP
# include <iostream>
# include <stdexcept>

class AForm;

class Bureaucrat
{
public:
	Bureaucrat();
	Bureaucrat(std::string name, int grade);
	~Bureaucrat();
	Bureaucrat(const Bureaucrat &other);
	Bureaucrat &operator=(const Bureaucrat &other);
	
	int			getGrade(void) const;
	std::string	getName(void) const;
	void		incrementGrade(void);
	void		decrementGrade(void);
	void		signForm(AForm &input);

	class	GradeTooHighException: public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
	class	GradeTooLowException: public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
private:
	const std::string	_name;
	int					_grade;
};

std::ostream &operator<<(std::ostream &out, Bureaucrat const &other);

#endif
