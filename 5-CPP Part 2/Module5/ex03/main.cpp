#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int	main(void)
{
	try
    {
        Intern a;
        Bureaucrat aa("aaa", 1);
        AForm *form = a.makeForm("test presidential test", "test");
        std::cout << *form;
        aa.signForm(*form);
        std::cout << *form;
        aa.executeForm(*form);
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << e.what();
    }
}
