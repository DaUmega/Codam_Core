#include "Classes.hpp"

Base::~Base(void)
{}

Base *Base::generate(void)
{
	Base *ret = NULL;
	srand(time(NULL));
	int	i = rand() % 3;

	switch(i)
	{
		case 0:
			ret = new A;
			break;
		case 1:
			ret = new B;
			break;
		case 2:
			ret = new C;
			break;
		default:
			break;
	}
	return ret;
}

void	Base::identify(Base *input)
{
	if (dynamic_cast<A*>(input))
		std::cout << "A\n";
	else if (dynamic_cast<B*>(input))
		std::cout << "B\n";
	else if (dynamic_cast<C*>(input))
		std::cout << "C\n";
}

void	Base::identify(Base &input)
{
	Base	test;
	try
	{
		test = dynamic_cast<A&>(input);
		std::cout << "A\n";
		return ;
	}
	catch (std::exception &e) {}
	try
	{
		test = dynamic_cast<B&>(input);
		std::cout << "B\n";
		return ;
	}
	catch (std::exception &e) {}
	try
	{
		test = dynamic_cast<C&>(input);
		std::cout << "C\n";
		return ;
	}
	catch (std::exception &e) {}
}
