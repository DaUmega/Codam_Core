/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:26:13 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 14:03:17 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(t_signal_handler handler)
{
	if (handler == SREADLINE)
	{
		rl_catch_signals = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (handler == SHEREDOC)
	{
		signal(SIGINT, heredoc_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (handler == SEXECUTOR)
	{
		signal(SIGINT, execution_sigint_handler);
		signal(SIGQUIT, execution_sigquit_handler);
	}
}
//	struct termios tio;
//	tcgetattr(STDIN_FILENO, &tio);
//	tcsetattr(STDIN_FILENO, TCSANOW, &tio);
	// return (SUCCESS);

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
