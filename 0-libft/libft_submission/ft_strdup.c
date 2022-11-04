/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 15:20:58 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 16:54:48 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	size_t	l;

	l = ft_strlen(s1);
	s = (char *)malloc(sizeof(s1) * (l + 1));
	if (!s)
		return (NULL);
	s = (char *)ft_memcpy((void *)s, (const void *)s1, l);
	s[l] = 0;
	return (s);
}

// int main()
// {
// 	char *s = ft_strdup("asdf");
// 	printf("%s\n", s);
// 	free(s);
// 	return 0;
// }