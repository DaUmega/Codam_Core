#include "Fixed.hpp"

Fixed::Fixed(void): _num(0)
{
	return;
}

Fixed::Fixed(int const input): _num(input << _bits)
{
	return;
}

Fixed::Fixed(float const input): _num(roundf(input * (1 << _bits)))
{
	return;
}

Fixed::~Fixed(void)
{
	return;
}

int	Fixed::getRawBits(void) const
{
	return (_num);
}

void Fixed::setRawBits(int const input)
{
	_num = input;
}

Fixed::Fixed(Fixed const &other): _num(other.getRawBits())
{
	return;
}

Fixed &Fixed::operator=(Fixed const &other)
{
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
	return ((float)(_num) / (float)(1 << _bits));
}

int Fixed::toInt(void) const
{
	return (_num >> _bits);
}

bool Fixed::operator>(Fixed const &other) const
{
	return (_num > other.getRawBits());
}

bool Fixed::operator<(Fixed const &other) const
{
	return (_num < other.getRawBits());
}

bool Fixed::operator>=(Fixed const &other) const
{
	return (_num >= other.getRawBits());
}

bool Fixed::operator<=(Fixed const &other) const
{
	return (_num <= other.getRawBits());
}

bool Fixed::operator==(Fixed const &other) const
{
	return (_num == other.getRawBits());
}

bool Fixed::operator!=(Fixed const &other) const
{
	return (_num != other.getRawBits());
}

Fixed Fixed::operator+(Fixed const &other)
{
	return Fixed(toFloat() + other.toFloat());
}

Fixed Fixed::operator-(Fixed const &other)
{
	return Fixed(toFloat() - other.toFloat());
}

Fixed Fixed::operator*(Fixed const &other)
{
	return Fixed(toFloat() * other.toFloat());
}

Fixed Fixed::operator/(Fixed const &other)
{
	return Fixed(toFloat() / other.toFloat());
}

Fixed &Fixed::operator++(void)
{
	_num++;
	return *this;
}

Fixed &Fixed::operator--(void)
{
	_num--;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed temp(*this);
	operator++();
	return temp;
}

Fixed Fixed::operator--(int)
{
	Fixed temp(*this);
	operator--();
	return temp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if (a._num > b._num)
		return b;
	return a;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if (a._num < b._num)
		return b;
	return a;
}

Fixed const &Fixed::min(Fixed const &a, Fixed const &b)
{
	if (a._num > b._num)
		return b;
	return a;
}

Fixed const &Fixed::max(Fixed const &a, Fixed const &b)
{
	if (a._num < b._num)
		return b;
	return a;
}
