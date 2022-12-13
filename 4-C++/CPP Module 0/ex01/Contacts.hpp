#ifndef CONTACTS_HPP
#define CONTACTS_HPP

#include <string>
class Contact
{
public:
	void		AddOne(int i);
	void		Display();
private:
	int			index;
	std::string	FirstName;
	std::string	LastName;
	std::string	NickName;
	std::string	PhoneNumber;
	std::string	DarkestSecret;
};

class DongBook
{
public:
	void	Search();
	void	AddContact(int i);
private:
	Contact data[8];
};

#endif