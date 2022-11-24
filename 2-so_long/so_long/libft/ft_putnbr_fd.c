/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 22:45:39 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 22:55:50 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <fcntl.h>
#include "libft.h"

void	recur(int n, int fd)
{
	int	a;

	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n != 0)
	{
		a = n % 10 + '0';
		recur(n / 10, fd);
		write(fd, &a, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n != 0)
		recur(n, fd);
	else if (n == 0)
		write(fd, "0", 1);
}

// int main()
// {
// 	int fd = open("test", O_RDWR);
// 	ft_putnbr_fd(0, fd);
// 	close(fd);
// }