/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/03 13:37:37 by pdong         #+#    #+#                 */
/*   Updated: 2023/01/03 18:35:06 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

t_pipe	*pipe_creator(int n)
{
	t_pipe	*ans;
	t_pipe	*temp;
	int		i;

	i = 0;
	ans = NULL;
	while (i < n)
	{
		temp = ft_lnew(i);
		ft_ladd_end(&ans, temp);
		i++;
	}
	return (ans);
}

void	close_unrelated_fd(t_pipe **pipes, int i)
{
	t_pipe	*temp;

	temp = *pipes;
	while (temp)
	{
		if (temp->index == i)
			close(temp->fd[1]);
		if (temp->index == i + 1)
			close(temp->fd[0]);
		else
		{
			close(temp->fd[1]);
			close(temp->fd[0]);
		}
		temp = temp->next;
	}
}

void	pipe_ft(t_pipe **pipes)
{
	t_pipe	*temp;
	int		n;

	temp = *pipes;
	while (temp)
	{
		temp->pid = fork();
		if (temp->pid < 0)
			ft_error();
		if (temp->pid == 0)
		{
			close_unrelated_fd(pipes, temp->index);
			if (read(temp->fd[0], &n, sizeof(int)) < 0)
				ft_error();
			n = n + 5;
			if (!temp->next)
			{
				ft_printf("%d\n", n);
				exit(EXIT_SUCCESS);
			}
			if (write(temp->next->fd[1], &n, sizeof(int)) < 0)
				ft_error();
		}
		temp = temp->next;
	}
}

void	leakchk(void)
{
	system("leaks -q pipex");
}

int	main(void)
{
	t_pipe	*temp;
	int		i;

	atexit(leakchk);
	i = 0;
	temp = pipe_creator(5);
	close_unrelated_fd(&temp, -1);
	ft_printf("%d\n", temp->next->next->fd[0]);
	if (write(temp->fd[1], &i, sizeof(int)) < 0)
		ft_error();
	pipe_ft(&temp);
	while (temp)
	{
		waitpid(temp->pid, NULL, 0);
		temp = temp->next;
	}
	exit(EXIT_SUCCESS);
}
