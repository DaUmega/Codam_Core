#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <stdexcept>
#include <vector>
#include <map>

class RPN
{
public:
	RPN();
	~RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);

	int		calculate(const std::string &input);

private:
	bool	operatorCheck(char c);
	int		operation(char op, int first, int second);
};
