#include "ScalarConverter.hpp"

int	main(void)
{
	try
    {
        Bureaucrat test("Bureaucrat", 150);
        try
        {
            test.decrementGrade();
        }
        catch (std::exception & e)
        {
            std::cout << e.what();
        }
        std::cout << test;
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << e.what();
    }
}
