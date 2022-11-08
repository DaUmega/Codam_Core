/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 15:18:33 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 14:17:00 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

// int main()
// {
// 	int a;
// 	int b;

// 	a = ft_isascii('\n');
// 	b = isascii('\n');
// 	printf("A:%d\n", a);
// 	printf("B:%d\n", b);
// }