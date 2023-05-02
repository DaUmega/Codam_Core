#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main(void)
{
	try
    {
        Bureaucrat a("a", 150);
        Form first("first", 90, 160);
        std::cout << a << '\n';
        std::cout << "Before first being signed "<< first << '\n';
        a.signForm(first);
        std::cout << "After first being signed "<< first << '\n';
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << '\n';
    }
    
    try
    {
        Bureaucrat b("b", 150);
        Form second("second", 150, 150);

        std::cout << b << '\n';
        std::cout << second << '\n';
        b.signForm(second);
        std::cout << second << '\n';
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << '\n';
    }
}
