#include "iter.hpp"

template<typename T>
void	test(T &value)
{
	if (std::is_same<T, int>::value)
        value += 1;
    std::cout << value << "\n";
}

int	main(void)
{
	std::string	test1[] = {"blah", "BLAH", "1234", "test"};
	int			test2[] = {1, 2, 3, 4, 5};

	iter(test1, 4, test<std::string>);
	iter(test2, 5, test<int>);
}
