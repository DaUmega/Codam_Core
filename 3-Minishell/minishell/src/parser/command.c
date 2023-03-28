/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:35:01 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 13:54:50 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_cmd(t_command *cmd)
{
	t_list	*tmp;
	t_redir	*redir;

	tmp = cmd->arguments;
	while (tmp)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
	tmp = cmd->redirs;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		free(redir->filename);
		free(redir);
		free(tmp);
		tmp = tmp->next;
	}
	free(cmd);
}

char	**get_arguments(t_command *cmd)
{
	t_list	*tmp;
	char	**arguments;
	int32_t	i;

	if (!cmd->arguments)
		return (NULL);
	arguments = ft_calloc(ft_lstsize(cmd->arguments) + 1, sizeof(char *));
	if (!arguments)
	{
		perror("calloc fail");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (cmd->arguments)
	{
		arguments[i] = cmd->arguments->content;
		tmp = cmd->arguments;
		cmd->arguments = cmd->arguments->next;
		free(tmp);
		i++;
	}
	return (arguments);
}

t_redir	*get_next_redir(t_command *cmd)
{
	t_redir	*current;
	t_list	*tmp;

	if (!cmd->redirs)
		return (NULL);
	current = cmd->redirs->content;
	tmp = cmd->redirs;
	cmd->redirs = cmd->redirs->next;
	free(tmp);
	return (current);
}

t_command	*get_next_command(t_command_table *ct)
{
	t_command	*current;
	t_list		*tmp;

	if (!ct->commands)
		return (NULL);
	current = ct->commands->content;
	tmp = ct->commands;
	ct->commands = ct->commands->next;
	free(tmp);
	return (current);
}

t_command	*construct_command(t_list **tokens)
{
	t_command	*command;
	char		*token;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		exit(EXIT_FAILURE);
	while (*tokens)
	{
		token = (*tokens)->content;
		if (is_delimiter(*token))
		{
			*tokens = (*tokens)->next;
			break ;
		}
		if (!is_redir(*token)
			&& !ft_lstadd_backnew(&command->arguments,
				ft_strdup((*tokens)->content)))
			return (NULL);
		if (is_redir(*token)
			&& !ft_lstadd_backnew(&command->redirs, construct_redir(tokens)))
			return (NULL);
		*tokens = (*tokens)->next;
	}
	return (command);
}
