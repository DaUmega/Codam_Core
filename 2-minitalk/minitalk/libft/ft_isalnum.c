/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 14:55:40 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 14:17:28 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

// int main()
// {
// 	int a;
// 	int b;

// 	a = ft_isalnum('.');
// 	b = isalnum('.');
// 	printf("A:%d\n", a);
// 	printf("B:%d\n", b);
// }