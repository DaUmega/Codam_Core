/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 14:19:53 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/15 15:46:31 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>
#include "libft.h"

long long	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long long	ans;

	i = 0;
	neg = 1;
	ans = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		ans = 10 * ans + (str[i++] - '0');
	return (ans * neg);
}

// int main () 
// {
//    const char str[50] = "  \n\f -1234123123123a567  ";
//    long long a = ft_atoi(str);
//    printf("%lld\n", a);
//    return(0);
// }