#include "Fixed.hpp"

Fixed::Fixed(void): _num(0)
{
	std::cout << "Default constructor called\n";
}

Fixed::Fixed(int const input): _num(input << Fixed::_bits)
{
	std::cout << "Int constructor called\n";
}

Fixed::Fixed(float const input): _num(roundf(input * (1 << Fixed::_bits)))
{
	std::cout << "Float constructor called\n";
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called\n";
}

int	Fixed::getRawBits(void) const
{
	return (this->_num);
}

Fixed::Fixed(Fixed const &other): _num(other.getRawBits())
{
	std::cout << "Copy constructor called\n";
}

Fixed &Fixed::operator=(Fixed const &other)
{
	std::cout << "Copy assignment operator called\n";
	this->_num = other.getRawBits();
	return (*this);
}

std::ostream &operator<<(std::ostream &out, Fixed const &input)
{
	out << input.toFloat();
	return (out);
}

float Fixed::toFloat(void) const
{
	return ((float)(this->_num) / (float)(1 << Fixed::_bits));
}

int Fixed::toInt(void) const
{
	return (this->_num >> Fixed::_bits);
}
