#pragma once
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

template<typename T>
class MutantStack : public std::stack<T>
{
public:
	typedef T	*iterator;
	iterator	begin(void) 
	{
		iterator ret = &this->top();
		for (unsigned int i = 1; i < this->size(); i++)
			ret--;
		return ret;
	}
	iterator	end(void) 
	{
		return (&this->top() + 1);
	}
private:
};
