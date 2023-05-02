#include "Form.hpp"

Form::Form(void): _name("Form"), _signed(false), _signGrade(1), _execGrade(1)
{
	std::cout << "Form constructor called.\n";
}

Form::Form(std::string name, int signGrade, int execGrade): 
_name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
	if (signGrade < 1 || execGrade < 1)
		throw GradeTooHighException();
	else if (signGrade > 150 || execGrade > 150)
		throw GradeTooLowException();
	std::cout << "Form constructor called.\n";
}

Form::~Form(void)
{
	std::cout << "Form destructor called.\n";
}

Form::Form(Form const &other): 
_name(other._name), _signed(other._signed), _signGrade(other._signGrade), _execGrade(other._execGrade)
{}

Form &Form::operator=(Form const &other)
{
	if (this != &other)
	{
		_signed = other._signed;
		_signGrade = other._signGrade;
		_execGrade = other._execGrade;
	}
	return *this;
}

int	Form::getSignGrade(void) const
{
	return _signGrade;
}

int	Form::getExecGrade(void) const
{
	return _execGrade;
}

std::string	Form::getName(void) const
{
	return _name;
}

bool	Form::getSigned(void) const
{
	return _signed;
}

void	Form::beSigned(Bureaucrat &input)
{
	if (input.getGrade() > _signGrade)
		throw Form::GradeTooLowException();
	_signed = true;
	std::cout << input.getName() << " signed " << _name;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return ("Grade too HIGH!\n");
}

const char* Form::GradeTooLowException::what() const throw()
{
	return ("Grade too LOW!\n");
}

std::ostream &operator<<(std::ostream &out, Form const &other)
{
	out << "Form name: " << other.getName()
	<< ", Sign Grade: " << other.getSignGrade()
	<< ", Grade to execute: " << other.getExecGrade()
	<< ", Signed: " << other.getSigned() << std::endl;
    return (out);
}
