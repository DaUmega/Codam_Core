/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:34:53 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 13:57:30 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_type	set_type(char *symbol, size_t len)
{
	if (!ft_strncmp("<", symbol, len))
		return (INPUT);
	else if (!ft_strncmp("<<", symbol, len))
		return (HEREDOC);
	else if (!ft_strncmp(">", symbol, len))
		return (OUTPUT);
	return (APPEND);
}

t_redir	*construct_redir(t_list **tokens)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
	{
		perror("calloc fail");
		exit(EXIT_FAILURE);
	}
	redir->type = set_type((*tokens)->content, ft_strlen((*tokens)->content));
	*tokens = (*tokens)->next;
	redir->filename = ft_strdup((char *)(*tokens)->content);
	return (redir);
}
