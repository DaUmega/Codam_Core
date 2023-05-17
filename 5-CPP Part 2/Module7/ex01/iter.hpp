#pragma once
#include <iostream>

template<typename T, typename U, typename V>
void	iter(T *addr, U len, V function)
{
	for (U i = 0; i < len; i++)
		function(addr[i]);
}
