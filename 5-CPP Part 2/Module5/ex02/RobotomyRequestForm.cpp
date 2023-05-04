#include "RobotomyRequestForm.hpp"
#include <time.h>

RobotomyRequestForm::RobotomyRequestForm(void): AForm("RobotomyRequestForm", 72, 45)
{
	_target = "Default";
	std::cout << "RobotomyRequestForm constructor called.\n";
}

RobotomyRequestForm::RobotomyRequestForm(std::string target): AForm("RobotomyRequestForm", 72, 45)
{
	_target = target;
	std::cout << "RobotomyRequestForm created with target: " << _target << "\n";
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
	std::cout << "RobotomyRequestForm destructor called.\n";
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &other): AForm(other)
{
	_target = other._target;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(RobotomyRequestForm const &other)
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

void	RobotomyRequestForm::execute(Bureaucrat const &other) const
{
	srand(time(NULL));
	int random = rand();
	
	try
	{
		if (other.getGrade() > this->getExecGrade())
			throw(GradeTooLowException());
		else if (!this->getSigned())
			throw(UnsignedException());
		else
		{
			std::cout << "Drilling Noises\n";
			if (random %2 == 0)
				std::cout << _target << " has been robotomized.\n";
			else
				std::cout << "Robotomy failed.\n";
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}
}
