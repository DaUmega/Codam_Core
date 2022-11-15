/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fivesort.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 15:42:31 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/15 15:42:32 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

int	minindex(t_lst **a)
{
	t_lst	*temp;
	int		min;
	int		index;
	int		imin;

	temp = *a;
	min = temp->content;
	index = 0;
	imin = 0;
	while (temp)
	{
		if (min > temp->content)
		{
			min = temp->content;
			imin = index;
		}
		temp = temp->next;
		index++;
	}
	return (imin);
}

void	fiverotate(t_lst **a, int size)
{
	int	index;

	index = minindex(a);
	while (index != 0)
	{
		if (index > size / 2)
		{
			ft_rrotate(a);
			ft_printf("rra\n");
			index++;
		}
		else
		{
			ft_rotate(a);
			ft_printf("ra\n");
			index--;
		}
		if (index == size)
			index = 0;
	}
}

void	fivesort(t_lst **a, t_lst **b)
{
	int		count;

	count = lstsize(a);
	while (count > 3)
	{
		fiverotate(a, lstsize(a));
		ft_push(a, b);
		ft_printf("pb\n");
		count--;
	}
	twosort(a, b);
	threesort(a, b);
}
