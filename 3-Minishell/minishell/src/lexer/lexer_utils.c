/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:41:13 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:41:14 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_quotechar(const char c)
{
	if (c == '\"' || c == '\'')
	{
		return (true);
	}
	return (false);
}

int32_t	is_tokenchar(const char *str)
{
	if (*str == '|')
		return (1);
	else if (*str == '<' || *str == '>')
	{
		if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
			return (2);
		return (1);
	}
	return (0);
}

void	ft_skip_whitespaces(const char **input)
{
	while (ft_iswhitespace(**input))
		(*input)++;
}
