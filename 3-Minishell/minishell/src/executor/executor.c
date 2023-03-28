/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dritsema <dritsema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/25 17:28:55 by dritsema      #+#    #+#                 */
/*   Updated: 2023/03/26 04:00:24 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int32_t	redirect(t_redir *redir, t_type type)
{
	char	*er_str;

	if (!open_redir(redir->filename, type))
	{
		er_str = ft_strjoin("Minishell: ", redir->filename);
		perror(er_str);
		free(er_str);
		return (errno);
	}
	return (SUCCESS);
}

int32_t	setup_redirects(t_command *command)
{
	t_redir	*redir;
	int32_t	ret;

	ret = SUCCESS;
	redir = get_next_redir(command);
	while (redir)
	{
		ret = redirect(redir, redir->type);
		free(redir->filename);
		free(redir);
		if (ret)
			return (errno);
		redir = get_next_redir(command);
	}
	return (ret);
}

t_builtin	builtin_lookup(char *cmd)
{
	const static t_builtin	lookup[] = {
	{.name = "echo", .func = ft_echo},
	{.name = "cd", .func = ft_cd},
	{.name = "pwd", .func = ft_pwd},
	{.name = "export", .func = ft_export},
	{.name = "unset", .func = ft_unset},
	{.name = "env", .func = ft_env},
	{.name = "exit", .func = ft_exit},
	{NULL, NULL}};
	int32_t					i;

	i = 0;
	while (lookup[i].name != NULL
		&& ft_strncmp(lookup[i].name, cmd, ft_strlen(cmd) + 1))
		i++;
	return (lookup[i]);
}

int32_t	execute_builtin(char **arguments, t_minishell *shell)
{
	t_builtin	builtin_function;
	int32_t		ret;

	builtin_function = builtin_lookup(arguments[0]);
	if (builtin_function.name == NULL)
		return (-1);
	ret = builtin_function.func(arguments, shell);
	ft_matrixfree(&arguments);
	return (ret);
}

int32_t	wait_for_child_processes(pid_t pid)
{
	int32_t	status;

	status = 0;
	close(STDIN_FILENO);
	waitpid(pid, &status, WUNTRACED);
	while (wait(NULL) != -1 && errno != ECHILD)
		;
	if (g_exitcode == E_CTRL_C)
		return (E_CTRL_C);
	if (g_exitcode == S_EXEC_QUIT)
	{
		printf("Quit: 3\n");
		return (WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}
