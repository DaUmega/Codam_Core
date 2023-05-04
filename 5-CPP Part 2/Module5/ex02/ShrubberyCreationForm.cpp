#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void): AForm("ShrubberyCreationForm", 145, 137)
{
	_target = "Default";
	std::cout << "ShrubberyCreationForm constructor called.\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("ShrubberyCreationForm", 145, 137)
{
	_target = target;
	std::cout << "ShrubberyCreationForm created with target: " << _target << "\n";
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	std::cout << "ShrubberyCreationForm destructor called.\n";
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &other): AForm(other)
{
	_target = other._target;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm const &other)
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

void	ShrubberyCreationForm::execute(Bureaucrat const &other) const
{
	try
	{
		if (other.getGrade() > this->getExecGrade())
			throw(GradeTooLowException());
		else if (!this->getSigned())
			throw(UnsignedException());
		else
		{
			std::ofstream	buffer(_target + "_shrubbery");
			if (!buffer)
				throw(FileCreateException());
			buffer << "       _-_\n\
    /~~   ~~\\\n\
 /~~         ~~\\\n\
{               }\n\
 \\  _-     -_  /\n\
   ~  \\\\ //  ~\n\
_- -   | | _- _\n\
  _ -  | |   -_\n\
      // \\\\\n";
			buffer.close();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what();
	}
}

const char* ShrubberyCreationForm::FileCreateException::what() const throw()
{
	return ("File creation error.\n");
}
