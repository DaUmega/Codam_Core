#include "Contacts.hpp"

int main()
{
	DongBook	data;
	std::string	input;
	int			index = 0;

	while (1)
	{
		std::cout << "Welcome to the Dong Book! Please enter a command. (ADD/SEARCH/EXIT)\n";
		std::getline(std::cin, input);
		if (std::cin.eof() || input == "EXIT")
			break;
		else if (input == "ADD")
		{
			if (data.AddContact(index))
				index++;
			if (index == 8)
				index = 0;
		}
		else if (input == "SEARCH")
			data.Search();
		else
			std::cout << "Invalid Input.\n";
	}
	return 0;
}
