/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lists.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 21:04:48 by pdong         #+#    #+#                 */
/*   Updated: 2023/01/03 18:15:40 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	ft_error(void)
{
	ft_printf("Error: %s\n", strerror(errno));
	exit(EXIT_FAILURE);
}

t_pipe	*ft_lnew(int index)
{
	t_pipe	*node;

	node = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!node || pipe(node->fd) < 0)
		ft_error();
	node->prev = NULL;
	node->index = index;
	node->next = NULL;
	return (node);
}

void	ft_ladd_end(t_pipe **lst, t_pipe *new)
{
	t_pipe	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

int	lstsize(t_pipe **a)
{
	t_pipe	*temp;
	int		i;

	if (!a || !*a)
		return (0);
	temp = *a;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_debug(t_pipe **lst)
{
	t_pipe	*temp;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (temp)
	{
		ft_printf("%d\n%d\n%d\n%p\n%p\n", temp->index, temp->fd[0], temp->fd[1], temp->prev, temp->next);
		temp = temp->next;
	}
	ft_printf("\n");
}
