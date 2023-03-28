/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:25:11 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:27:28 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

// 30 is an arbitrary number that most likely is not used as a legit exit code.
// Thus it only ever happens when interupting heredoc.
void	execution_sigint_handler(int sig)
{
	(void)sig;
	g_exitcode = E_CTRL_C;
}

void	execution_sigquit_handler(int sig)
{
	(void)sig;
	g_exitcode = S_EXEC_QUIT;
}

void	heredoc_sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exitcode = S_HEREDOC;
}

// void	executor_signal_setup(void)
// {
// 	signal(SIGINT, execution_signal_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }