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
	int	getRawBits(void) const;
	Fixed(Fixed const &other);
	Fixed &operator=(Fixed const &other);
	float toFloat(void) const;
	int	toInt(void) const;
private:
	int					_num;
	static const int	_bits = 8;
};

std::ostream &operator<<(std::ostream &out, Fixed const &input);

#endif
