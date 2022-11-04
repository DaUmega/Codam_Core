/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 22:31:18 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 22:57:31 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <fcntl.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

// int	main(void)
// {
// 	int fd = open("test", O_RDWR);
// 	ft_putendl_fd("test", fd);
// 	close(fd);
// }
