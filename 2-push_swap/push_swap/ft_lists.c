/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lists.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 21:04:48 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/14 22:14:08 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

void	ft_error(void)
{
	ft_printf("Error\n");
	exit(EXIT_FAILURE);
}

t_lst	*ft_lnew(int content)
{
	t_lst	*ls;

	ls = (t_lst *)malloc(sizeof(t_lst));
	if (!ls)
		ft_error();
	ls->prev = NULL;
	ls->content = content;
	ls->next = NULL;
	return (ls);
}

void	ft_ladd_end(t_lst **lst, t_lst *new)
{
	t_lst	*temp;

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

void	ft_ladd_start(t_lst **lst, t_lst *new)
{
	t_lst	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->prev)
			temp = temp->prev;
		temp->prev = new;
		new->next = temp;
		*lst = new;
	}
}

int	lstsize(t_lst **a)
{
	t_lst	*temp;
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

// void	ft_debug(t_lst **lst)
// {
// 	t_lst	*temp;

// 	if (!lst || !*lst)
// 		return ;
// 	temp = *lst;
// 	while (temp)
// 	{
// 		ft_printf("%d\n%p\n%p\n", temp->content, temp->prev, temp->next);
// 		temp = temp->next;
// 	}
// 	ft_printf("\n");
// }
