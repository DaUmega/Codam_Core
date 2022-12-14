#ifndef CONTACTS_HPP
# define CONTACTS_HPP
# include <iostream>
# include <string>

class Contact
{
public:
	bool		AddOne(int i);
	void		SimpleDisplay(void);
	void		DetailDisplay(void);
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
	void	Search(void);
	bool	AddContact(int i);
private:
	Contact data[8];
};

#endif
