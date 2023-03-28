/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:05:49 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 04:05:49 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <minishell.h>

int	ft_env(char **arguments, t_minishell *shell)
{
	int32_t	i;

	(void)arguments;
	i = 0;
	while (shell->env[i])
	{
		printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
