#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <stdexcept>
#include <vector>
#include <map>

class BitcoinExchange
{
public:
	BitcoinExchange();
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	
	void	dbParse(void);
	void	inputParse(std::string input);

private:
	std::map<std::string, float>	_db;

	bool	dateCheck(const std::string &input);
	bool	valueCheck(const std::string &input);
	float	getPrice(const std::string &input);
};
