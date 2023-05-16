#include "Serializer.hpp"

Serializer::Serializer(void)
{}

Serializer::~Serializer(void)
{}

Serializer::Serializer(Serializer const &other)
{
	(void)(other);
}

Serializer &Serializer::operator=(Serializer const &other)
{
	(void)(other);
	return *this;
}

uintptr_t	Serializer::serialize(Data *input)
{
	return (uintptr_t)input->value;
}

Data *Serializer::deserialize(uintptr_t input)
{
	Data	*ret = new Data;

	ret->value = input;
	return ret;
}
