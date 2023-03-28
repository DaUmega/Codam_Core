/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   analyzer_checks.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:41:17 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:41:18 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int32_t	pipe_check(t_list *tokens)
{
	if (!tokens->next)
		return (1);
	else if (!ft_strncmp(tokens->next->content, "|", 2))
		return (1);
	return (0);
}

int32_t	input_check(t_list *tokens)
{
	if (!tokens->next)
		return (1);
	else if (is_tokenchar(tokens->next->content))
		return (1);
	return (0);
}

int32_t	output_check(t_list *tokens)
{
	if (!tokens->next)
		return (1);
	else if (is_tokenchar(tokens->next->content))
		return (1);
	return (0);
}

int32_t	heredoc_check(t_list *tokens)
{
	if (!tokens->next)
		return (1);
	else if (is_tokenchar(tokens->next->content))
		return (1);
	return (0);
}

int32_t	append_check(t_list *tokens)
{
	if (!tokens->next)
		return (1);
	else if (is_tokenchar(tokens->next->content))
		return (1);
	return (0);
}
