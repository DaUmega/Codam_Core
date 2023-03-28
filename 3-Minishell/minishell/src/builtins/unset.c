/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:05:10 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 14:05:46 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	in_args(char **argv, char *env_line)
{
	int		i;
	char	*suffix;
	char	*var;

	i = 1;
	suffix = ft_strdup("=");
	while (suffix && argv[i])
	{
		var = ft_strjoin(argv[i], suffix);
		if (var
			&& !ft_strncmp(var, env_line, ft_strlen(var)))
			return (free(var), free(suffix), 1);
		free(var);
		if (argv[i]
			&& !ft_strncmp(argv[i], env_line, ft_strlen(argv[i]) + 1))
			return (free(suffix), 1);
		i++;
	}
	free(suffix);
	return (0);
}

void	unset_copy(char **argv, char **new_env, char **old_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_env[i])
	{
		if (!in_args(argv, old_env[i]))
		{
			new_env[j] = old_env[i];
			j++;
		}
		else
			free(old_env[i]);
		i++;
	}
	new_env[j] = NULL;
}

static int	get_env_len(char **arguments, char **env)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (env[i])
	{
		if (!in_args(arguments, env[i]))
			len++;
		i++;
	}
	return (len);
}

int	ft_unset(char **arguments, t_minishell *shell)
{
	char	**new_env;
	char	**new_expo;

	new_env = ft_calloc(get_env_len(arguments, shell->env) + 1, sizeof(char *));
	new_expo = ft_calloc(get_env_len(arguments, shell->expo) + 1,
			sizeof(char *));
	if (!new_env || !new_expo)
	{
		perror("calloc fail");
		exit(EXIT_FAILURE);
	}
	unset_copy(arguments, new_env, shell->env);
	unset_copy(arguments, new_expo, shell->expo);
	free(shell->env);
	free(shell->expo);
	shell->env = new_env;
	shell->expo = new_expo;
	return (0);
}
