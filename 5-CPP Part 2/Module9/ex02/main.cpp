#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	try
	{
		PmergeMe	test;
		test.sort(ac, av);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}
