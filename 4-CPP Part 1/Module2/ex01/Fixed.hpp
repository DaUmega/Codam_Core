#ifndef FIXED_HPP
# define FIXED_HPP
# include <iostream>
# include <cmath>

class Fixed
{
public:
	Fixed();
	Fixed(int const input);
	Fixed(float const input);
	~Fixed();
	int	getRawBits() const;
	Fixed(Fixed const &other);
	Fixed &operator=(Fixed const &other);
private:
	int					_num;
	static const int	_bits = 8;
};

#endif
