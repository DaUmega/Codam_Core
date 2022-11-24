/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 14:52:41 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 14:16:47 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// int main()
// {
// 	int a;
// 	int b;

// 	a = ft_isdigit('a');
// 	b = isdigit('a');
// 	printf("A:%d\n", a);
// 	printf("B:%d\n", b);
// }