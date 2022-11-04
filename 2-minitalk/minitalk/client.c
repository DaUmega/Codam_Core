/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 21:26:36 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/03 16:55:46 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <signal.h>
#include <stdlib.h>

static void	send_msg(int pid, char c)
{
	static int	i = 0;

	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(77);
		i++;
	}
	if (i == 8)
		i = 0;
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
	{
		ft_printf("Error, Usage: PID(Numbers) MESSAGE(Printable).");
		return (0);
	}
	while (av[1][i])
	{
		if (av[1][i] < '0' || av[1][i] > '9' || av[1][0] == '0')
			return (ft_printf("Error, Invalid PID."), 0);
		i++;
	}
	i = 0;
	while (av[2][i])
	{
		send_msg(ft_atoi(av[1]), av[2][i]);
		i++;
	}
	return (0);
}
