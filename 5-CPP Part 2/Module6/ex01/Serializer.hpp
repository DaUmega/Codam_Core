#pragma once
#include <iostream>
#include <stdint.h>

typedef struct thedata
{
	int	value;
}	Data;

class Serializer
{
public:
	Serializer();
	~Serializer();
	Serializer(const Serializer &other);
	Serializer &operator=(const Serializer &other);
	
	static uintptr_t	serialize(Data *input);
	static Data			*deserialize(uintptr_t input);
private:
};
