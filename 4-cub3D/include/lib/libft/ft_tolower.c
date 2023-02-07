/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 20:26:04 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/04 20:26:26 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <unistd.h>
// #include <xlocale.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

// int main()
// {
// 	int a;
// 	int b;

// 	a = ft_tolower('b');
// 	b = tolower('b');
// 	write(1, &a, 1);
// 	write(1, &b, 1);
// }