/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:42:35 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:42:36 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int32_t	skip_single_quotes(char *str)
{
	int32_t	i;

	i = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			return (i + 1);
	}
	return (i);
}

int32_t	skip_double_quotes(char *str)
{
	int32_t	i;

	i = 0;
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i] == '\"')
			return (i + 1);
	}
	return (0);
}

// returns the length of the variable name that the string starts with.
int32_t	varkey_len(char *str)
{
	int32_t	i;

	i = 0;
	if (str[i] == '$')
	{
		i++;
		if (str[i] == '?' || str[i] == '~')
			return (i + 1);
	}
	else if (str[i] == '~')
		return (i + 1);
	while (valid_varchar(str[i]))
		i++;
	return (i);
}

// Skip whitespace. return the length of whitespace.
int32_t	skip_whitespace(char *str)
{
	int32_t	i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	return (i);
}

// state 0 is no quotes, 1 is double, 2 is single. 2 is never used.
int32_t	find_var_start(char *str, int32_t index)
{
	int32_t	i;
	int32_t	quoted;

	i = 0;
	quoted = 0;
	while (str[i] && i < index)
	{
		if (str[i] == '\'' && quoted == 0)
			i += skip_single_quotes(&str[i]);
		else if (str[i] == '\"')
			quoted = (quoted - 1) * -1;
		i++;
	}
	while (str[i] != '$' && str[i] != '~' && str[i])
	{
		if (str[i] == '\'' && quoted == 0)
			i += skip_single_quotes(&str[i]);
		else if (str[i] == '\"')
			quoted = (quoted - 1) * -1;
		i++;
	}
	return (i);
}
