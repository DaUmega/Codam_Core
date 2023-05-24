#include "RPN.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage: ./RPN \"<expression>\"\n";
		return 0;
	}

	std::string		input = av[1];
	RPN	test;
	try
	{
		std::cout << test.calculate(input);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}
