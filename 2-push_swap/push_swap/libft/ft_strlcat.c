/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 19:21:57 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/13 21:53:32 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	j = 0;
	temp = ft_strlen(dst);
	while (i < dstsize - 1 && (src[j]))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	if (ft_strlen(dst) >= dstsize)
		temp = dstsize;
	i = temp + ft_strlen(src);
	return (i);
}

// #include <stdio.h>
// int main () 
// {
//    char dest[16] = "rrrrrrrrrrrrrrr";
//    printf("Before strlcat dest = %s\n", dest);
//    int a = ft_strlcat((void *)0, "123456789123456789", 0);
//    printf("After strlcat dest = %s & %d\n", dest, a);
//    return(0);
// }