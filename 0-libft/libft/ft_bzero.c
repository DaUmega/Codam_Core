/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 20:12:31 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/06 16:53:02 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = 0;
		i++;
	}
}

// int main()
// {
//     int i = 0;
// 	char str1[50] = "GeeksForGeeks is for programming geeks.";
// 	char str2[50] = "GeeksForGeeks is for programming geeks.";
//     ft_bzero(str1, 3);
// 	bzero(str2, 3);
//     while(i < 7)
// 	{
// 		printf("My version:  %c\n", str1[i]);
// 		printf("Actual ans:  %c\n", str2[i]);
// 		i++;
// 	}
//     return 0;
// }