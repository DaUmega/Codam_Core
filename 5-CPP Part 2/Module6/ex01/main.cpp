#include "Serializer.hpp"

int	main(void)
{
	Data    *test = new Data;
    Data    *temp;

    test->value = 10;
    uintptr_t value2 = Serializer::serialize(test);
    temp = Serializer::deserialize(value2);

    std::cout << temp->value << "\n" << value2 << std::endl;
    delete test;
    delete temp;
}
