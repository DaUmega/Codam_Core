/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:05:45 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 04:05:46 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit(char **arguments, t_minishell *shell)
{
	(void)arguments;
	(void)shell;
	rl_clear_history();
	if (arguments[1])
		exit(ft_atoi(arguments[1]));
	else
		exit(0);
	return (0);
}
