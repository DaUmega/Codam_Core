#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void): AForm("PresidentialPardonForm", 25, 5)
{
	_target = "Default";
	std::cout << "PresidentialPardonForm constructor called.\n";
}

PresidentialPardonForm::PresidentialPardonForm(std::string target): AForm("PresidentialPardonForm", 25, 5)
{
	_target = target;
	std::cout << "PresidentialPardonForm created with target: " << _target << "\n";
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
	std::cout << "PresidentialPardonForm destructor called.\n";
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &other): AForm(other)
{
	_target = other._target;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &other)
{
	if (this != &other)
	{
		this->setName(other.getName());
		this->setSign(other.getSigned());
		this->setSGrade(other.getSignGrade());
		this->setEGrade(other.getExecGrade());
		_target = other._target;
	}
	return *this;
}

void	PresidentialPardonForm::execute(Bureaucrat const &other) const
{
	try
	{
		if (other.getGrade() > this->getExecGrade())
			throw(GradeTooLowException());
		else if (!this->getSigned())
			throw(UnsignedException());
		else
			std::cout << _target << " has been pardoned by Zaphod Beeblebrox.\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}
}
