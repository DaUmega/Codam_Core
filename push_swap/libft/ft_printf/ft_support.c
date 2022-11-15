/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_support.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 16:48:22 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/03 13:09:36 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long long nbr, const char *hex)
{
	int	a;
	int	len;

	len = 0;
	if (nbr != 0)
	{
		a = nbr % ft_strlen(hex);
		len += ft_putptr(nbr / ft_strlen(hex), hex) + 1;
		write(1, &hex[a], 1);
		return (len);
	}
	else
		return (0);
}

int	ft_p(va_list arg)
{
	int	len;

	len = 0;
	write(1, "0x", 2);
	len = ft_putptr((size_t)va_arg(arg, size_t), "0123456789abcdef") + 2;
	if (len == 2)
		len = ft_putchar('0') + 2;
	return (len);
}

int	ft_di(va_list arg, const char *s)
{
	int	len;

	len = 0;
	len = ft_putall(va_arg(arg, int), s);
	if (len == 0)
		len = ft_putchar('0');
	return (len);
}

int	ft_uxx(va_list arg, const char *s)
{
	int	len;

	len = 0;
	len = ft_putpos((unsigned int)va_arg(arg, int), s);
	if (len == 0)
		len = ft_putchar('0');
	return (len);
}

int	ft_putall(int nbr, const char *hex)
{
	int			a;
	int			len;
	long long	temp;

	len = 0;
	temp = (long long)nbr;
	if (temp < 0)
	{
		write(1, "-", 1);
		temp = -temp;
		len = 1;
	}
	if (temp != 0)
	{
		a = temp % ft_strlen(hex);
		len += ft_putall(temp / ft_strlen(hex), hex) + 1;
		write(1, &hex[a], 1);
		return (len);
	}
	else
		return (0);
}
