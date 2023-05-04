#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"

int	main(void)
{
	try
    {
        Bureaucrat a("aaa", 140);
        ShrubberyCreationForm first("first");
        std::cout << a;
        std::cout << first;
        a.signForm(first);
        std::cout << first;
        first.execute(a);
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << e.what();
    }
}
