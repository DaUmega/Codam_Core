#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main(void)
{
	try
    {
        Bureaucrat a("aaa", 140);
        ShrubberyCreationForm form("first");
        std::cout << a;
        std::cout << form;
        a.signForm(form);
        std::cout << form;
        a.executeForm(form);
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << e.what();
    }
    try
    {
        Bureaucrat b("bbb", 40);
        RobotomyRequestForm two("second");
        std::cout << b;
        std::cout << two;
        b.signForm(two);
        std::cout << two;
        b.executeForm(two);
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << e.what();
    }
    try
    {
        Bureaucrat c("ccc", 1);
        PresidentialPardonForm three("3");
        std::cout << c;
        std::cout << three;
        c.signForm(three);
        std::cout << three;
        c.executeForm(three);
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << e.what();
    }
}
