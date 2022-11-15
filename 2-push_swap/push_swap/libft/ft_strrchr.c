/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 20:58:38 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/07 21:34:52 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

// int main () 
// {
//    const char str[50] = "";
//    char *ans;
//    printf("Before memmove dest = %s\n", str);
//    ans = ft_strrchr(str, 0);
//    printf("After memmove dest = %s\n", ans);
//    return(0);
// }