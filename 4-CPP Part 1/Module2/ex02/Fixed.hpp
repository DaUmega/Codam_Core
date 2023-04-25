#ifndef FIXED_HPP
# define FIXED_HPP
# include <iostream>
# include <cmath>

class Fixed
{
public:
	Fixed(void);
	Fixed(int const input);
	Fixed(float const input);
	~Fixed(void);

	int		getRawBits(void) const;
	void	setRawBits(int const input);
	Fixed(Fixed const &other);

	Fixed	&operator=(Fixed const &other);
	bool	operator>(Fixed const &other) const;
	bool	operator<(Fixed const &other) const;
	bool	operator>=(Fixed const &other) const;
	bool	operator<=(Fixed const &other) const;
	bool	operator==(Fixed const &other) const;
	bool	operator!=(Fixed const &other) const;
	Fixed	operator+(Fixed const &other);
	Fixed	operator-(Fixed const &other);
	Fixed	operator*(Fixed const &other);
	Fixed	operator/(Fixed const &other);
	Fixed	&operator++(void);
	Fixed	&operator--(void);
	Fixed	operator++(int);
	Fixed	operator--(int);

	static Fixed	&max(Fixed &a, Fixed &b);
	static Fixed	&min(Fixed &a, Fixed &b);
	static const Fixed	&max(Fixed const &a, Fixed const &b);
	static const Fixed	&min(Fixed const &a, Fixed const &b);
	float	toFloat(void) const;
	int		toInt(void) const;
private:
	int					_num;
	static const int	_bits = 8;
};

std::ostream &operator<<(std::ostream &out, Fixed const &input);

#endif
