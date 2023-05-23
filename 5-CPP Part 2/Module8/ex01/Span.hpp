#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

class Span
{
public:
	Span();
	Span(unsigned int N);
	~Span();
	Span(const Span &other);
	Span &operator=(const Span &other);
	
	void			addNumber(int input);
	void			addNumbers(int input);
	unsigned int	shortestSpan(void);
	unsigned int	longestSpan(void);

	class MaxSize : public std::exception
	{
		public:
			virtual const char *what(void) const throw();
	};
	class NoSpan : public std::exception
	{
		public:
			virtual const char *what(void) const throw();
	};

private:
	unsigned int		_N;
	std::vector<int>	_vec;
};
