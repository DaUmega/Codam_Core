/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils3.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:58:59 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 14:05:10 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int32_t	init_first_pipe(int32_t *pipe_fds)
{
	if (pipe(pipe_fds) == -1)
		return (ERROR);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		return (ERROR);
	close(pipe_fds[1]);
	return (SUCCESS);
}

int32_t	prepare_next_pipe(int32_t *pipe_fds, int32_t *std_fds, bool last)
{
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	if (last)
	{
		if (dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO) == -1)
			return (ERROR);
	}
	else
	{
		if (pipe(pipe_fds) == -1)
			return (ERROR);
		if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
			return (ERROR);
		close(pipe_fds[1]);
	}
	return (SUCCESS);
}

int32_t	execute_pipeline(t_command_table *ct,
	int32_t *std_fds, t_minishell *shell)
{
	t_command	*cmd;
	int32_t		pipe_fds[2];
	pid_t		pid;

	if (init_first_pipe(pipe_fds) == -1)
		return (ERROR);
	cmd = get_next_command(ct);
	while (cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fds[0]);
			execute_pipe_command(cmd, shell);
		}
		free_cmd(cmd);
		cmd = get_next_command(ct);
		if (!cmd)
			break ;
		if (ct->commands)
			prepare_next_pipe(pipe_fds, std_fds, false);
		else
			prepare_next_pipe(pipe_fds, std_fds, true);
	}
	return (wait_for_child_processes(pid));
}

int32_t	execute_command_table(t_command_table *ct,
	int32_t *std_fds, t_minishell *shell)
{
	if (ct->commands->next == NULL)
		return (execute_simple_command(get_next_command(ct), shell));
	return (execute_pipeline(ct, std_fds, shell));
}

int32_t	executor(t_minishell *shell)
{
	t_command_table	*ct;
	int32_t			status;
	int32_t			std_fds[2];

	status = 0;
	setup_signals(SEXECUTOR);
	ct = get_next_command_table(&shell->ast);
	std_fds[STDIN_FILENO] = dup(STDIN_FILENO);
	std_fds[STDOUT_FILENO] = dup(STDOUT_FILENO);
	while (ct)
	{
		status = execute_command_table(ct, std_fds, shell);
		free(ct);
		dup2(std_fds[STDIN_FILENO], STDIN_FILENO);
		dup2(std_fds[STDOUT_FILENO], STDOUT_FILENO);
		ct = get_next_command_table(&shell->ast);
	}
	close(std_fds[STDIN_FILENO]);
	close(std_fds[STDOUT_FILENO]);
	return (status);
}
