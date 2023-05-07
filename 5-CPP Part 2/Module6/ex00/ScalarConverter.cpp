#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void): _name("Default"), _grade(2)
{
	std::cout << "Default constructor called with name: Default and grade: 2\n";
}

Bureaucrat::Bureaucrat(std::string name, int grade): _name(name), _grade(grade)
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	std::cout << _name << " has been created with grade: " << _grade << std::endl;
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << "Bureaucrat destructor called.\n";
}

Bureaucrat::Bureaucrat(Bureaucrat const &other): _name(other._name), _grade(other._grade)
{}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &other)
{
	if (this != &other)
		_grade = other._grade;
	return *this;
}

int	Bureaucrat::getGrade(void) const
{
	return _grade;
}

std::string	Bureaucrat::getName(void) const
{
	return _name;
}

void	Bureaucrat::incrementGrade(void)
{
	if (_grade <= 1)
		throw Bureaucrat::GradeTooHighException();
	else
		_grade--;
}

void	Bureaucrat::decrementGrade(void)
{
	if (_grade >= 150)
		throw Bureaucrat::GradeTooLowException();
	else
		_grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade too HIGH!\n");
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade too LOW!\n");
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &other)
{
	out << other.getName() << ", bureaucrat grade " << other.getGrade() << std::endl;
	return (out);
}
