#include <iostream>

int main()
{
	std::string words = "HI THIS IS BRAIN";
	std::string *stringPTR = &words;
	std::string &stringREF = words;

	std::cout	<< "string address: " << &words << "\npointer address: " 
				<< stringPTR << "\nreference address: " << &stringREF << "\n";
	std::cout	<< "string value: " << words << "\npointer value: " 
				<< *stringPTR << "\nreference value: " << stringREF << "\n";
}
