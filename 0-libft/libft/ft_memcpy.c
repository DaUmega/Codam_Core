/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 20:23:38 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/04 19:20:07 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return (dst);
}

// int main () 
// {
//    const char src[50] = "123456789";
//    char dest[50];
//    strcpy(dest,"Hellooooooo!!");
//    printf("Before memcpy dest = %s\n", dest);
//    ft_memcpy(dest + 1, src, 3);
//    printf("After memcpy dest = %s\n", dest);
//    return(0);
// }