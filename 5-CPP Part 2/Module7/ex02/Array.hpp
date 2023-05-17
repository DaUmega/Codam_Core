#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class Array
{
public:
	Array() : _size(0), _arr(NULL) {}
	Array(unsigned int input) : _size(input), _arr(new T[input]) {}
	~Array() { delete[] _arr; }
	Array(const Array &other) : _size(other._size), _arr(new T[other._size])
	{
		for (unsigned int i = 0; i < _size; i++)
			_arr[i] = other._arr[i];
	}
	Array	 &operator=(const Array &other)
	{
		if (this != &other)
		{
			delete[] _arr;
			_arr = new T[other._size];
			_size = other._size;
			for (unsigned int i = 0; i < _size; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}
	
	T	&operator[](unsigned int input)
	{
		if (input >= _size)
			throw std::exception();
		return _arr[input];
	}
	unsigned int	size(void) const
	{
		return _size;
	}

private:
	unsigned int	_size;
	T				*_arr;
};
