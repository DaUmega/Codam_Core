#include "AForm.hpp"

AForm::AForm(void): _name("AForm"), _signed(false), _signGrade(1), _execGrade(1)
{
	std::cout << "AForm constructor called.\n";
}

AForm::AForm(std::string name, int signGrade, int execGrade): 
_name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
	if (signGrade < 1 || execGrade < 1)
		throw GradeTooHighException();
	else if (signGrade > 150 || execGrade > 150)
		throw GradeTooLowException();
	std::cout << "AForm constructor called.\n";
}

AForm::~AForm(void)
{
	std::cout << "AForm destructor called.\n";
}

AForm::AForm(AForm const &other): 
_name(other._name), _signed(other._signed), _signGrade(other._signGrade), _execGrade(other._execGrade)
{}

AForm &AForm::operator=(AForm const &other)
{
	if (this != &other)
	{
		_signed = other._signed;
		_signGrade = other._signGrade;
		_execGrade = other._execGrade;
	}
	return *this;
}

int	AForm::getSignGrade(void) const
{
	return _signGrade;
}

int	AForm::getExecGrade(void) const
{
	return _execGrade;
}

std::string	AForm::getName(void) const
{
	return _name;
}

bool	AForm::getSigned(void) const
{
	return _signed;
}

void	AForm::beSigned(Bureaucrat &input)
{
	if (input.getGrade() > _signGrade)
		throw AForm::GradeTooLowException();
	_signed = true;
	std::cout << input.getName() << " signed " << _name;
}

const char* AForm::GradeTooHighException::what() const throw()
{
	return ("Grade too HIGH!\n");
}

const char* AForm::GradeTooLowException::what() const throw()
{
	return ("Grade too LOW!\n");
}

std::ostream &operator<<(std::ostream &out, AForm const &other)
{
	out << "AForm name: " << other.getName()
	<< ", Sign Grade: " << other.getSignGrade()
	<< ", Grade to execute: " << other.getExecGrade()
	<< ", Signed: " << other.getSigned() << std::endl;
    return (out);
}
