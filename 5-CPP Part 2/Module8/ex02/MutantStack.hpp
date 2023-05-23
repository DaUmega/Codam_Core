#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

template<typename T>
class MutantStack : public std::stack<T>
{
public:
	MutantStack() {}
	~MutantStack() {}
	MutantStack(const MutantStack &other) {*this = copy;}
	MutantStack &operator=(const MutantStack &other) {*this = other; return *this;}
	
	typedef T	*iterator;
	iterator	begin(void) 
	{
		iterator ret = &this->top();
		for (unsigned int i = 0; i < size(); i++)
			ret--;
		return ret;
	}
	iterator	end(void) 
	{
		return (top() + 1);
	}
private:
};
