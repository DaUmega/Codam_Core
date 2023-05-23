#include "easyfind.hpp"

int	main(void)
{
	std::vector<int>    test;

    for (int i = 0; i < 10; i++)
        test.push_back(i);
    try
    {
        std::cout << "test1: " << *easyfind(test, 5) << "\n";
        std::cout << "test2: " << *easyfind(test, 15) << "\n";
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }
}
