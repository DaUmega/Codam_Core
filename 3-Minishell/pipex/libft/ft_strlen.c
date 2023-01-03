/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 16:48:22 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/13 20:19:47 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// int main()
// {
// 	size_t a;
// 	size_t b;

// 	a = ft_strlen("asdf\n");
// 	b = strlen("asdf\n");
// 	printf("A:%d\n", a);
// 	printf("B:%d\n", b);
// }