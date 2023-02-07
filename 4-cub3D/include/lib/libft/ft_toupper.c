/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 20:10:59 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/04 20:25:18 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <unistd.h>
// #include <xlocale.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

// int main()
// {
// 	int a;
// 	int b;

// 	a = ft_toupper('b');
// 	b = toupper('b');
// 	write(1, &a, 1);
// 	write(1, &b, 1);
// }