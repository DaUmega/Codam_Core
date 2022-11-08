/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 20:29:05 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/04 21:41:11 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) != (char)c)
	{
		if (!*(s + i))
			return (NULL);
		i++;
	}
	return ((char *)(s + i));
}

// int main () 
// {
//    const char str[50] = "123456389";
//    char *ans;
//    printf("Before memmove dest = %s\n", str);
//    ans = ft_strchr(str, '3');
//    printf("After memmove dest = %s\n", ans);
//    return(0);
// }