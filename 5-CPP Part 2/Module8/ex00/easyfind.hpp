#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

template<typename T>
typename T::iterator	easyfind(T container, int i)
{
	typename T::iterator ret;

	ret = std::find(container.begin(), container.end(), i);
	if (ret == container.end())
		throw(std::runtime_error("Failed to find the value.\n"));
	return ret;
}
