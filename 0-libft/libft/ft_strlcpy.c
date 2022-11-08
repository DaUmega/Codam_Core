/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 21:27:47 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/07 19:32:36 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = 0;
	return (ft_strlen(src));
}

// int main () 
// {
//    const char src[50] = "coucou";
//    char dest[50];
//    strcpy(dest, "Helloo");
//    printf("Before strlcpy dest = %s\n", dest);
//    int a = ft_strlcpy(dest, src, 2);
//    printf("After strlcpy dest = %c & %d\n", dest[2], a);
//    return(0);
// }