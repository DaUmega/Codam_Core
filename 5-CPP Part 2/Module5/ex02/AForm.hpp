#ifndef AFORM_HPP
# define AFORM_HPP
# include "Bureaucrat.hpp"
# include <fstream>
# include <filesystem>
# include <string>

class Bureaucrat;

class AForm
{
public:
	AForm();
	AForm(std::string name, int signGrade, int execGrade);
	virtual	~AForm();
	AForm(const AForm &other);
	AForm &operator=(const AForm &other);
	
	int			getExecGrade(void) const;
	int			getSignGrade(void) const;
	std::string	getName(void) const;
	bool		getSigned(void) const;
	void		beSigned(Bureaucrat &input);
	void		setName(std::string input);
	void		setSign(bool input);
	void		setSGrade(int input);
	void		setEGrade(int input);

	virtual	void	execute(Bureaucrat const &other) const = 0;

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
	class	UnsignedException: public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
private:
	std::string		_name;
	bool			_signed;
	int				_signGrade;
	int				_execGrade;
protected:
	std::string		_target;
};

std::ostream &operator<<(std::ostream &out, AForm const &other);

#endif
