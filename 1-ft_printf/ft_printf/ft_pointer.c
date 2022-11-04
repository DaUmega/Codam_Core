/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_pointer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 13:05:25 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/11 14:28:57 by pdong         ########   odam.nl         */
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
