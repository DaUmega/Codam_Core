#include "Bureaucrat.hpp"
#include "AAForm.hpp"

int	main(void)
{
	try
    {
        Bureaucrat a("aaa", 80);
        AForm first("first", 90, 150);
        std::cout << a;
        std::cout << first;
        a.signForm(first);
        std::cout << first;
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << e.what();
    }
    
    try
    {
        Bureaucrat b("bbb", 150);
        AForm second("second", 150, 150);

        std::cout << b;
        std::cout << second;
        b.signForm(second);
        std::cout << second;
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << e.what();
    }
}
