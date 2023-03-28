/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:43:01 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 17:32:09 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_cmd(t_command *cmd, t_minishell *shell)
{
	expand_argument_list(&cmd->arguments, shell);
	expand_redirect_list(&cmd->redirs, shell);
}

void	expand_cmd_table(t_command_table *cmd_table, t_minishell *shell)
{
	t_command	*cmd;
	t_list		*iter;

	iter = cmd_table->commands;
	while (iter)
	{
		cmd = (t_command *)iter->content;
		expand_cmd(cmd, shell);
		iter = iter->next;
	}
}

int32_t	expander(t_minishell *shell)
{
	t_command_table	*cmd_table;
	t_list			*ast;

	ast = shell->ast;
	while (ast)
	{
		cmd_table = (t_command_table *)ast->content;
		expand_cmd_table(cmd_table, shell);
		ast = ast->next;
	}
	return (SUCCESS);
}
