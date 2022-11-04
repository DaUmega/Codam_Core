/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 21:03:59 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/04 21:33:33 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

// int main() 
// {
//   char str1[] = "abcD", str2[] = "abcd";
//   int result;
//   result = ft_strncmp(str1, str2, 0);
//   printf("%d\n", result);
//   result = strncmp(str1, str2, 0);
//   printf("%d\n", result);
//   return 0;
// }