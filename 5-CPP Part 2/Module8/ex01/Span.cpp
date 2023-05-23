#include "Span.hpp"

Span::Span(void) : _N(0)
{}

Span::Span(unsigned int N) : _N(N)
{}

Span::~Span(void)
{}

Span::Span(Span const &other)
{
	_N = other._N;
    _vec = other._vec;
}

Span &Span::operator=(Span const &other)
{
	_N = other._N;
    _vec = other._vec;
	return *this;
}

const char  *Span::MaxSize::what() const throw()
{
    return ("Maximum size reached.\n");
}

const char  *Span::NoSpan::what() const throw()
{
    return ("There is no Span.\n");
}

void    Span::addNumber(int input)
{
    if (_vec.size() >= _N)
        throw(MaxSize());
    _vec.push_back(input);
}

void    Span::addNumbers(int input)
{
    int i = 0;
    
    if (_vec.size() + input >= _N)
        throw(MaxSize());
    while (_vec.size() < _N && i < input)
    {
        _vec.push_back(i);
        i++;
    }
}

unsigned int    Span::shortestSpan(void)
{
    unsigned int ret = UINT_MAX;
    
    if (_vec.size() == 0)
        return 0;
    for (unsigned int i = 0; i < _vec.size(); i++)
    {
        for (unsigned int j = i + 1; j < _vec.size(); j++)
        {
            if ((unsigned int)std::abs(_vec[i] - _vec[j]) < ret)
                ret = std::abs(_vec[i] - _vec[j]);
        }
    }
    return ret;
}

unsigned int    Span::longestSpan(void)
{
    unsigned int ret = 0;
    
    for (unsigned int i = 0; i < _vec.size(); i++)
    {
        for (unsigned int j = i + 1; j < _vec.size(); j++)
        {
            if ((unsigned int)std::abs(_vec[i] - _vec[j]) > ret)
                ret = std::abs(_vec[i] - _vec[j]);
        }
    }
    return ret;
}
