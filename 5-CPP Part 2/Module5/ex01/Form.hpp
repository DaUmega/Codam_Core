#ifndef FORM_HPP
# define FORM_HPP
# include "Bureaucrat.hpp"

class Form
{
public:
	Form();
	Form(std::string name, int signGrade, int execGrade);
	~Form();
	Form(const Form &other);
	Form &operator=(const Form &other);
	
	int			getExecGrade(void) const;
	int			getSignGrade(void) const;
	std::string	getName(void) const;
	bool		getSigned(void) const;
	void		beSigned(const Bureaucrat &input);

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
	bool				_signed;
	int					_signGrade;
	int					_execGrade;
};

std::ostream &operator<<(std::ostream &out, Form const &other);

#endif
