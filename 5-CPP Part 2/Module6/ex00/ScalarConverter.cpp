#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter(void)
{}

ScalarConverter::~ScalarConverter(void)
{}

ScalarConverter::ScalarConverter(ScalarConverter const &other)
{
	(void)(other);
}

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &other)
{
	(void)(other);
	return *this;
}

template <typename T>	
T	ScalarConverter::convert(const std::string &input) const
{
	T	value;

	if (std::is_same<T, char>::value)
	{
		try { value = std::stoi(input); }
		catch(const std::exception &e)
			{ std::cout << "char: impossible\n"; return value; }
		if (value < 0 || value > 127)
			std::cout << "char: impossible\n"; 
		else if (value < 32 || value > 126)
            std::cout << "char: Non displayable\n";
		else
			std::cout << "char: '" << value << "'" << std::endl;
		return value;
	}
	else if (std::is_same<T, int>::value)
	{
		try { value = std::stoi(input); }
		catch(const std::exception &e)
			{ std::cout << "int: impossible\n"; return value; }
		std::cout << "int: " << value << std::endl;
		return value;
	}
	else if (std::is_same<T, float>::value)
	{
		float temp;
		try { temp = std::stof(input); }
		catch(const std::exception &e)
			{ std::cout << "float: impossible\n"; return temp;}
		std::cout << std::setprecision(1) << std::fixed << "float: " << temp << "f" << std::endl;
		return temp;
	}
	else if (std::is_same<T, double>::value)
	{
		double temp;
		try { temp = std::stod(input); }
		catch(const std::exception &e)
			{ std::cout << "double: impossible\n"; return temp;}
		std::cout << std::setprecision(1) << std::fixed << "double: " << temp << std::endl;
		return temp;
	}
}

template char ScalarConverter::convert<char>(const std::string &input) const;
template int ScalarConverter::convert<int>(const std::string &input) const;
template float ScalarConverter::convert<float>(const std::string &input) const;
template double ScalarConverter::convert<double>(const std::string &input) const;
