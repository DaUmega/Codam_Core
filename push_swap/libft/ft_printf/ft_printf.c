/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 12:35:34 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/01 19:38:43 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	ft_putpos(unsigned int nbr, const char *hex)
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
		len += ft_putpos(temp / ft_strlen(hex), hex) + 1;
		write(1, &hex[a], 1);
		return (len);
	}
	else
		return (0);
}

int	matcher(va_list arg, const char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = ft_putchar(va_arg(arg, int));
	if (c == 's')
		len = ft_putstr(va_arg(arg, char *));
	if (c == 'p')
		len = ft_p(arg);
	if (c == 'd' || c == 'i')
		len = ft_di(arg, "0123456789");
	if (c == 'u')
		len = ft_uxx(arg, "0123456789");
	if (c == 'x')
		len = ft_uxx(arg, "0123456789abcdef");
	if (c == 'X')
		len = ft_uxx(arg, "0123456789ABCDEF");
	if (c == '%')
		len = ft_putchar('%');
	return (len);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		len;
	va_list	arg;

	i = 0;
	len = 0;
	va_start(arg, s);
	while (s[i++])
	{
		if (s[i - 1] == '%')
		{
			len += matcher(arg, s[i]);
			if (s[i])
				i++;
		}
		else
		{
			ft_putchar(s[i - 1]);
			len++;
		}
	}
	va_end(arg);
	return (len);
}

// int main()
// {
// 	int c = 'a';
// 	int d = 'b';
// 	long long f = 0;
// 	int i = ft_printf("%s\n", "test");
// 	int j = printf("%s\n", "test");
// 	printf("%d\n%d\n", i, j);
// 	return (0);
// }