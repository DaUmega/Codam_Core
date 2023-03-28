/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:57:23 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:58:29 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_env_paths(char **envp, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	*suffix;
	char	**paths;

	i = 0;
	cmd_path = NULL;
	paths = get_env_paths(envp);
	suffix = ft_strjoin("/", cmd);
	if (paths && suffix)
	{
		while (paths[i])
		{
			cmd_path = ft_strjoin(paths[i], suffix);
			if (!access(cmd_path, X_OK))
				break ;
			free(cmd_path);
			cmd_path = NULL;
			i++;
		}
	}
	free(suffix);
	ft_matrixfree(&paths);
	return (cmd_path);
}

char	*get_cmd_path(char **envp, char *cmd)
{
	char	*cmd_path;

	if (!cmd)
		return (0);
	if (ft_strncmp("./", cmd, 2) && ft_strncmp("/", cmd, 1))
	{
		cmd_path = check_env_paths(envp, cmd);
		if (cmd_path)
		{
			if (is_dir(cmd_path))
				return (free(cmd_path), NULL);
			return (cmd_path);
		}
	}
	if (!access(cmd, X_OK))
	{
		if (is_dir(cmd))
			return (NULL);
		return (cmd);
	}
	return (NULL);
}

void	execute_child_command(t_minishell *shell, char **arguments)
{
	char	*command_path;

	reset_signals();
	command_path = get_cmd_path(shell->env, arguments[0]);
	if (access(command_path, X_OK))
	{
		write(2, "Minishell: ", 12);
		write(2, arguments[0], ft_strlen(arguments[0]));
		write(2, ": command not found\n", 21);
	}
	execve(command_path, arguments, shell->env);
	exit(127);
}

// Needs to always exit even if it is builtin
int32_t	execute_pipe_command(t_command *cmd, t_minishell *shell)
{
	char	**arguments;
	int32_t	status;

	reset_signals();
	status = setup_redirects(cmd);
	arguments = get_arguments(cmd);
	if (!arguments || status)
		exit(status);
	status = execute_builtin(arguments, shell);
	free(cmd);
	if (status >= 0)
		exit(status);
	execute_child_command(shell, arguments);
	return (ft_matrixfree(&arguments), 0);
}

int32_t	execute_simple_command(t_command *cmd, t_minishell *shell)
{
	pid_t		pid;
	int32_t		status;
	char		**arguments;

	status = setup_redirects(cmd);
	arguments = get_arguments(cmd);
	if (!arguments || status)
	{
		ft_matrixfree(&arguments);
		free_cmd(cmd);
		return (status);
	}
	free_cmd(cmd);
	status = execute_builtin(arguments, shell);
	if (status >= 0)
		return (status);
	pid = fork();
	if (pid == 0)
		execute_child_command(shell, arguments);
	return (ft_matrixfree(&arguments), wait_for_child_processes(pid));
}
