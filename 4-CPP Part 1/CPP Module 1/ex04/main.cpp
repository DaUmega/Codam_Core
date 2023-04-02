#include <iostream>
#include <fstream>
#include <string>

int main(int ac, char **av)
{
	std::ifstream	ifs;
	std::string		content;
	char			c;

	if (ac != 4)
	{
		std::cout << "usage: ./mysed <filename> <old_string> <new_string>\n";
		return (0);
	}
	ifs.open(av[1]);
	if (ifs.fail())
	{
		std::cout << "File Open Error.\n";
		return (0);
	}
	while (ifs)
	{
		c = ifs.get();
		content += c;
	}
	std::cout << content;
	return (0);
}
