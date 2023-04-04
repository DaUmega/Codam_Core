#include <iostream>
#include <fstream>
#include <string>

void	str_replace(std::string s, char **av)
{
	std::ofstream	ofs;
	int				index;

	ofs.open((std::string(av[1]) + ".replace").c_str());
	if (ofs.fail())
	{
		std::cout << "Outfile Open Error.\n";
		return ;
	}
	for (int i = 0; i < int(s.size()); i++)
	{
		index = s.find(av[2], i);
		if (index >= 0 && index == i)
		{
			ofs << av[3];
			i += std::string(av[2]).size() - 1;
		}
		else
			ofs << s[i];
	}
	ofs.close();
}

int main(int ac, char **av)
{
	std::ifstream	ifs;
	std::string		line;
	std::string		content;

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
	while (getline(ifs, line))
		content += line + '\n';
	ifs.close();
	str_replace(content, av);
	return (0);
}
