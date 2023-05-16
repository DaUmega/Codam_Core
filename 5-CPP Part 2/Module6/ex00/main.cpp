#include "ScalarConverter.hpp"

int	main(int ac, char **av)
{
	ScalarConverter test;

    if (ac != 2)
        std::cout << "Usage: ./out <string to convert>\n";
    else
    {
        std::string input(av[1]);
        test.convert<char>(input);
        test.convert<int>(input);
        test.convert<float>(input);
        test.convert<double>(input);
    }
}
