#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error: could not open file.\n";
		return 0;
	}

	std::string		input = av[1];
	BitcoinExchange	test;
	test.dbParse();
	test.inputParse(input);
	
	return 0;
}
