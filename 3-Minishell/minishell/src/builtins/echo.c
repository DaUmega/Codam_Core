/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:05:53 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 04:05:54 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	validflag(char *flag)
{
	int32_t	i;

	if (flag && flag[0] == '-')
	{
		i = 1;
		while (flag[i] && flag[i] == 'n')
			i++;
		if (!flag[i] && i > 1)
			return (1);
	}
	return (0);
}

int32_t	ft_echo(char **arguments, t_minishell *shell)
{
	int32_t	i;
	bool	newline;

	(void)shell;
	newline = true;
	i = 1;
	while (validflag(arguments[i]))
	{
		newline = false;
		i++;
	}
	while (arguments[i])
	{
		write(1, arguments[i], ft_strlen(arguments[i]));
		i++;
		if (arguments[i])
			write(1, " ", 1);
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
