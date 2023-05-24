#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{}

BitcoinExchange::~BitcoinExchange(void)
{}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
    _db = other._db;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
    if (this != &other)
        _db = other._db;
	return *this;
}

bool    BitcoinExchange::dateCheck(const std::string &input)
{
    std::tm test = {};
    std::istringstream  iss(input);
    iss >> std::get_time(&test, "%Y-%m-%d");
    return !iss.fail();
}

bool    BitcoinExchange::valueCheck(const std::string &input)
{
    long value;
    try
    {
        value = std::stol(input);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
    if (value < 0)
        std::cout << "Error: not a positive number.\n";
    else if (value > 1000)
        std::cout << "Error: too large a number.\n";
    return (value >= 0 && value <= 1000);
}

void    BitcoinExchange::dbParse(void)
{
    std::ifstream file("data.csv");
    if (!file)
    {
        std::cout << "Error: could not open data.csv file.\n";
        return ;
    }

    std::string line;
    while (getline(file, line))
    {
        std::istringstream  iss(line);
        std::string         date, value;
        if (getline(iss, date, ',') && getline(iss, value, ','))
            _db[date] = atof(value.c_str());
    }
    file.close();
}

void    BitcoinExchange::inputParse(void)
{
    float   ret;
    bool    first = true;
    
    std::ifstream file("input.txt");
    if (!file)
    {
        std::cout << "Error: could not open input.txt file.\n";
        return ;
    }

    std::string line;
    while (getline(file, line))
    {
        if (first)
        {
            first = false;
            continue;
        }

        std::istringstream  iss(line);
        std::string         date, value;
        if (!getline(iss, date, '|') || !getline(iss, value, '|'))
            std::cerr << "Error: bad input => " << line << "\n";
        else if (!dateCheck(date) || !valueCheck(value))
            continue;
        else
        {
            ret = stof(value) * getPrice(date);
            std::cout << date << " => " << value << " = " << ret << "\n";
        }
    }
    file.close();
}

float   BitcoinExchange::getPrice(const std::string &input)
{
    
    std::map<std::string, float>::iterator it = _db.upper_bound(input);
    if (it != _db.end())
        return it->second;
    return 0;
}
