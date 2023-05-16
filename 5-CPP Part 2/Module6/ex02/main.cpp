#include "Classes.hpp"

int	main(void)
{
	Base    *test;

    test = Base::generate();
    Base &ref = *test;

    Base::identify(test);
    Base::identify(ref);
    delete test;
}
