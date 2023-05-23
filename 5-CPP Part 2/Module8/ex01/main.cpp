#include "Span.hpp"

int	main(void)
{
	Span	span(5);
    Span    span2(10001);

	span.addNumber(6);
	span.addNumber(3);
	span.addNumber(17);
	span.addNumber(9);
	span.addNumber(11);

	std::cout << "shortest span: " << span.shortestSpan() << std::endl;
	std::cout << "longest span: " << span.longestSpan() << std::endl;
    try
	{
		span.addNumber(11);
	}
	catch(std::exception &e)
	{
		std::cout << e.what();
	}

    try
	{
		span2.addNumbers(10005);
	}
	catch(std::exception &e)
	{
		std::cout << e.what();
	}
    std::cout << "shortest span: " << span2.shortestSpan() << std::endl;
	std::cout << "longest span: " << span2.longestSpan() << std::endl;
    try
	{
		span2.addNumber(11);
	}
	catch(std::exception &e)
	{
		std::cout << e.what();
	}
}
