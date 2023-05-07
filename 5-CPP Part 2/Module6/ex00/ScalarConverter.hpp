#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP
# include <iostream>
# include <stdexcept>

class ScalarConverter
{
public:
	ScalarConverter();
	ScalarConverter(std::string name, int grade);
	~ScalarConverter();
	ScalarConverter(const ScalarConverter &other);
	ScalarConverter &operator=(const ScalarConverter &other);
	
	int			getGrade(void) const;
	std::string	getName(void) const;
	void		incrementGrade(void);
	void		decrementGrade(void);

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

std::ostream &operator<<(std::ostream &out, ScalarConverter const &other);

#endif
