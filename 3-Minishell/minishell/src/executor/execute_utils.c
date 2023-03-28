/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:57:27 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 04:00:18 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_dir(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY);
	if (fd == -1 && errno == EISDIR)
	{
		return (1);
	}
	close(fd);
	return (0);
}

static bool	openfile(int *fd, char *path, t_type type)
{
	if (type == HEREDOC)
	{
		*fd = open(path, O_RDONLY);
		unlink(path);
	}
	else if (type == INPUT)
		*fd = open(path, O_RDONLY);
	else if (type == OUTPUT)
		*fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (type == APPEND)
		*fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (*fd == -1)
		return (false);
	return (true);
}

bool	protected_dup2(int fd, t_type type)
{
	int	ret;

	if (type == INPUT || type == HEREDOC)
		ret = dup2(fd, STDIN_FILENO);
	else
		ret = dup2(fd, STDOUT_FILENO);
	if (ret == -1)
		return (false);
	return (true);
}

bool	open_redir(char *path, t_type type)
{
	int32_t	fd;

	if (!openfile(&fd, path, type))
		return (false);
	if (!protected_dup2(fd, type))
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

char	**get_env_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			paths = ft_split(&envp[i][5], ':');
		i++;
	}
	return (paths);
}
