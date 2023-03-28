/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable_expand.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:42:16 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 17:29:59 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_specialvar(char *var_name)
{
	if (!ft_strncmp(var_name, "~", 1))
		return (1);
	if (!ft_strncmp(var_name, "$", 2))
		return (1);
	if (!ft_strncmp(var_name, "$?", 2))
		return (1);
	if (!ft_strncmp(var_name, "$~", 2))
		return (1);
	if (ft_isdigit(var_name[1]))
		return (1);
	return (0);
}

// Get special variable values.
char	*special_variable(char *var_name, t_minishell *shell)
{
	int32_t	i;

	i = 0;
	if (!ft_strncmp(var_name, "~", 1))
	{
		while (shell->env[i])
		{
			if (!ft_strncmp(shell->env[i], "HOME=", 5))
			{
				return (ft_strdup(&shell->env[i][5]));
			}
			i++;
		}
	}
	else if (!ft_strncmp(var_name, "$?", 2))
		return (ft_itoa(g_exitcode));
	if (ft_isdigit(var_name[i + 1]))
	{
		i++;
		while (valid_varchar(var_name[i]))
			i++;
		return (ft_substr(var_name, 1, i - 1));
	}
	return (ft_strdup(var_name));
}

void	get_env_var2(t_minishell *shell, char *var, int32_t len, char **str)
{
	int32_t	i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], var + 1, len - 1)
			&& shell->env[i][len - 1] == '=')
		{
			free(*str);
			*str = ft_strdup(&shell->env[i][len]);
		}
		i++;
	}
}

// get the correct environment variable for a given "var_name" string.
char	*get_env_var(char *var_name, t_minishell *shell)
{
	int32_t	len;
	char	*str;

	len = 0;
	if (is_specialvar(var_name))
		return (free(var_name), special_variable(var_name, shell));
	if (var_name[len] == '$')
		len++;
	while (valid_varchar(var_name[len]))
		len++;
	str = ft_calloc(1, 1);
	if (!str)
	{
		perror("calloc fail");
		exit(EXIT_FAILURE);
	}
	get_env_var2(shell, var_name, len, &str);
	free (var_name);
	return (str);
}

char	*expand_variables(char *str, t_minishell *shell)
{
	int32_t	i;
	int32_t	start;
	char	*tmp;
	char	*new_str;

	i = 0;
	start = 0;
	new_str = ft_calloc(1, 1);
	if (!new_str)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		i = find_var_start(str, i);
		if (!str[i])
			break ;
		tmp = ft_substr(str, start, i - start);
		new_str = ft_strjoin_free_free(new_str, tmp);
		tmp = get_env_var(ft_substr(str, i, varkey_len(&str[i])), shell);
		new_str = ft_strjoin_free_free(new_str, tmp);
		i += varkey_len(&str[i]);
		start = i;
	}
	return (ft_strjoin_free(new_str, &str[start]));
}
