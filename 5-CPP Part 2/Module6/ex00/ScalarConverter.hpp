#pragma once
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <iomanip>

class ScalarConverter
{
public:
	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(const ScalarConverter &other);
	ScalarConverter &operator=(const ScalarConverter &other);
	
	template <typename T> 
	T	convert(const std::string &input) const;
private:
};
