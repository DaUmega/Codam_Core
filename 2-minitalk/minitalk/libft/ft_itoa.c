/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 20:37:02 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/13 18:33:09 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	sizer(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	if (i == 0)
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	int			len;
	long long	a;
	char		*ans;

	len = sizer(n);
	a = (long long)n;
	if (n < 0)
	{
		len += 1;
		a = -a;
	}
	ans = malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (NULL);
	ans[len] = 0;
	while (len-- > 0)
	{
		ans[len] = a % 10 + '0';
		a = a / 10;
	}
	if (n < 0)
		ans[0] = '-';
	return (ans);
}

// int main()
// {
// 	char *ans = ft_itoa(-2147483648);
// 	printf("%s\n", ans);
// 	free(ans);
// }