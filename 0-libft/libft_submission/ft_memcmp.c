/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 21:31:04 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/04 22:13:39 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
	{
		i++;
		if (i == n)
			return (0);
	}
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

// int main() 
// {
//   char str1[] = "abcdef", str2[] = "abcd";
//   int result;
//   result = ft_memcmp(str1, str2, 4);
//   printf("%d\n", result);
//   result = memcmp(str1, str2, 4);
//   printf("%d\n", result);
//   return 0;
// }