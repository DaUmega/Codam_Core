#include "Contacts.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>

void	Contact::SimpleDisplay(void)
{
	std::string	fname;
	std::string	lname;
	std::string	nname;

	if (!this->FirstName.empty())
	{
		fname = this->FirstName;
		lname = this->LastName;
		nname = this->NickName;
		if (fname.size() > 10)
		{
			fname.resize(10);
			fname[fname.size() - 1] = '.';
		}
		if (lname.size() > 10)
		{
			lname.resize(10);
			lname[lname.size() - 1] = '.';
		}
		if (nname.size() > 10)
		{
			nname.resize(10);
			nname[nname.size() - 1] = '.';
		}
		std::cout	<< "|" << std::setw(10) << this->index << "|" << std::setw(10) << fname
					<< "|" << std::setw(10) << lname << "|" << std::setw(10) << nname << "|\n";
	}
}

void	Contact::DetailDisplay(void)
{
	if (!this->FirstName.empty())
	{
		std::cout	<< "Index: " << this->index << "\n" << "First Name: " << this->FirstName << "\n"
					<< "Last Name: " << this->LastName << "\n" << "Nickname: " << this->NickName << "\n"
					<< "Phone Number: " << this->PhoneNumber << "\n" << "Darkest Secret: " << this->DarkestSecret << "\n";
	}
	else
		std::cout 	<< "There's nothing to show here!\n";
}

bool	Contact::AddOne(int i)
{
	std::string	fname;
	std::string	lname;
	std::string	nname;
	std::string	cell;
	std::string	secret;

	std::cout << "Please enter their First Name:\n";
	std::getline(std::cin, fname);
	std::cout << "Please enter their Last Name:\n";
	std::getline(std::cin, lname);
	std::cout << "Please enter their Nickname:\n";
	std::getline(std::cin, nname);
	std::cout << "Please enter their Phone Number:\n";
	std::getline(std::cin, cell);
	std::cout << "Please enter their Darkest Secret:\n";
	std::getline(std::cin, secret);
	if (std::cin.eof() || fname.empty() || lname.empty() || nname.empty() || cell.empty() || secret.empty())
	{
		std::cout << "Invalid inputs, please try again!\n";
		return 0;
	}
	else
	{
		this->index = i;
		this->FirstName = fname;
		this->LastName = lname;
		this->NickName = nname;
		this->PhoneNumber = cell;
		this->DarkestSecret = secret;
		std::cout << "Contact Successfully Added!\n";
		return 1;
	}
}

void	DongBook::Search(void)
{
	int 		i = 0;
	std::string	input;
	
	std::cout	<< "|" << std::setw(10) << "Index" << "|" << std::setw(10) << "First Name"
				<< "|" << std::setw(10) << "Last Name" << "|" << std::setw(10) << "Nickname" << "|\n";
	while (i < 8)
		this->data[i++].SimpleDisplay();
	std::cout << "Please enter an index number. (0-7)\n";
	std::getline(std::cin, input);
	if (std::cin.eof() || input[0] < '0' || input[0] > '7' || input[1])
		std::cout << "Bad Index, BAD!\n";
	else
	{
		std::istringstream(input) >> i;
		this->data[i].DetailDisplay();
	}
}

bool	DongBook::AddContact(int i)
{
	return (this->data[i].AddOne(i));
}
