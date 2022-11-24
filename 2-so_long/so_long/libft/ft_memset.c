/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 16:53:38 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/03 21:14:37 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)b;
	while (i < len)
	{
		s[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

// int main()
// {
//     char str1[50] = "GeeksForGeeks is for programming geeks.";
// 	char str2[50] = "GeeksForGeeks is for programming geeks.";
//     ft_memset(str1, '.', 8*sizeof(char));
// 	memset(str2, '.', 8*sizeof(char));
//     printf("My version:  %s\n", str1);
// 	printf("Actual ans:  %s\n", str2);
//     return 0;
// }