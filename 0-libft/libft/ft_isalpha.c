/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 14:26:09 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 14:17:13 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// int main()
// {
// 	int a;
// 	int b;

// 	a = ft_isalpha('A');
// 	b = isalpha('A');
// 	printf("A:%d\n", a);
// 	printf("B:%d\n", b);
// }