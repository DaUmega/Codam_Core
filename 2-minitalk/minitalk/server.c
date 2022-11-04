/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 20:08:02 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/03 16:46:14 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <signal.h>

static void	saction(int sig)
{
	static char	c = 0;
	static int	i = 0;

	if (sig == SIGUSR1)
		i++;
	if (sig == SIGUSR2)
	{
		c |= 1 << i;
		i++;
	}
	if (i == 8)
	{
		ft_printf("%c", c);
		c = 0;
		i = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = saction;
	sa.sa_flags = SA_RESTART;
	ft_printf("Server PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
