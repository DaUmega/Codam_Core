/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 16:44:05 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 14:17:44 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

// int main()
// {
// 	int a;
// 	int b;

// 	a = ft_isprint('\n');
// 	b = isprint('\n');
// 	printf("A:%d\n", a);
// 	printf("B:%d\n", b);
// }