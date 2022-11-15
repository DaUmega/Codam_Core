/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 20:45:05 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 16:30:44 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (dst > src)
	{
		i = len - 1;
		while (i > 0)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i--;
		}
		*(char *)(dst + i) = *(char *)(src + i);
	}
	else
	{
		while (i < len)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dst);
}

// int main () 
// {
//    char str[50] = "123456789";
//    printf("Before memmove dest = %s\n", str);
//    ft_memmove(&str[5], &str[4], 3);
//    printf("After memmove dest = %s\n", str);
//    return(0);
// }