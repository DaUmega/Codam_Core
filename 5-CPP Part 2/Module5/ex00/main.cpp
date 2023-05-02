#include "Bureaucrat.hpp"

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
            std::cout << e.what() << std::endl;
        }
        std::cout << test << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
