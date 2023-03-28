/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:35:27 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:35:28 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_ast(t_list **ast)
{
	t_command_table	*table;
	t_command		*command;
	t_list			*com_lst;
	t_list			*tmp;

	if (*ast)
	{
		table = (t_command_table *)(*ast)->content;
		com_lst = table->commands;
		while (com_lst)
		{
			command = com_lst->content;
			free_cmd(command);
			tmp = com_lst;
			com_lst = com_lst->next;
			free(tmp);
		}
		free(table);
		free(*ast);
		*ast = NULL;
	}
}

t_list	*construct_ast(t_list *tokens)
{
	t_list	*ast;

	if (tokens == NULL)
		return (NULL);
	ast = NULL;
	while (tokens)
	{
		if (!ft_lstadd_backnew(&ast, (void *)construct_command_table(&tokens)))
			return (NULL);
	}
	return (ast);
}
