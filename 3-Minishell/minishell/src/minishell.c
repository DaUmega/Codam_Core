/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:11:34 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 17:31:24 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tokens(t_list *tokens)
{
	printf("tokens:\n");
	while (tokens)
	{
		printf("[%s]\n", tokens->content);
		tokens = tokens->next;
	}
}

void	print_ast2(t_command *command)
{
	t_list	*args_lst;
	t_list	*redir_lst;
	t_redir	*tmp_redir;

	args_lst = command->arguments;
	printf("|  |  |  Arguments:\n");
	while (args_lst)
	{
		printf("|  |  |  |  [%p]->[%s]\n", args_lst, args_lst->content);
		args_lst = args_lst->next;
	}
	redir_lst = command->redirs;
	printf("|  |  |  Redirects:\n");
	while (redir_lst)
	{
		tmp_redir = redir_lst->content;
		printf("|  |  |  |  [%p]->[%s] - [%i]\n", tmp_redir,
			tmp_redir->filename, tmp_redir->type);
		redir_lst = redir_lst->next;
	}
}

void	print_ast(t_list *ast)
{
	t_command_table	*table;
	t_list			*com_lst;
	t_command		*command;
	t_list			*ast_lst;

	ast_lst = ast;
	while (ast_lst)
	{
		table = (t_command_table *)ast_lst->content;
		com_lst = table->commands;
		printf("ast [%p]:\n", ast_lst);
		printf("|  Table [%p]:\n", table);
		printf("|  |  Command count: %i\n", table->command_count);
		while (com_lst)
		{
			command = (t_command *)com_lst->content;
			printf("|  |  Command:\n");
			if (command)
				print_ast2(command);
			com_lst = com_lst->next;
		}
		ast_lst = ast_lst->next;
	}
}

/*
 * Abstract_syntax_tree gathers one or more command tables
 * It is only created when the input is valid
 */

int	minishell2(t_minishell *sheldon, char *command_line)
{
	sheldon->ast = parser(sheldon->tokens);
	ft_lstclear(&sheldon->tokens, free);
	expander(sheldon);
	if (g_exitcode == S_HEREDOC)
	{
		g_exitcode = 0;
		return (clear_ast(&sheldon->ast), free(command_line), SUCCESS);
	}
	g_exitcode = 0;
	g_exitcode = executor(sheldon);
	free(command_line);
	return (EXIT_SUCCESS);
}

int32_t	minishell(t_minishell *sheldon)
{
	char	*command_line;

	setup_signals(SREADLINE);
	command_line = readline(messages_lookup(PROMPT));
	if (!command_line && printf("\x1B[1AMinishell$ exit\n"))
		exit(E_GENERAL);
	if (!*command_line)
		return (free(command_line), SUCCESS);
	add_history(command_line);
	lexer(command_line, &sheldon->tokens);
	if (!sheldon->tokens)
		return (free(command_line), SUCCESS);
	if (analyzer(sheldon->tokens))
	{
		ft_lstclear(&sheldon->tokens, free);
		return (free(command_line), EXIT_FAILURE);
	}
	return (minishell2(sheldon, command_line));
}
