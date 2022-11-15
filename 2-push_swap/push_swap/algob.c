/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   algob.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 21:04:41 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/14 21:04:42 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"
#include <limits.h>

void	rlstsplit(t_lst **b, t_lst **a, int median, int buf)
{
	t_lst	*temp;
	int		i;
	int		j;

	temp = *b;
	i = buf / 2;
	j = INT_MAX;
	while (i >= 0)
	{
		if (temp->content >= median)
		{
			pushnsortb(a, b);
			i--;
		}
		else
		{
			if (j == INT_MAX)
				j = temp->content;
			ft_rotate(b);
			ft_printf("rb\n");
		}
		temp = *b;
	}
	if (j != INT_MAX)
		rlstsplit2(b, j);
}

void	rlstsplit2(t_lst **b, int j)
{
	t_lst	*temp;
	int		size;

	size = lstsize(b);
	temp = *b;
	if (getindexb(b, j) > size / 2)
	{
		while (temp->content != j)
		{
			ft_rrotate(b);
			ft_printf("rrb\n");
			temp = *b;
		}
	}
	else
	{
		while (temp->content != j)
		{
			ft_rotate(b);
			ft_printf("rb\n");
			temp = *b;
		}
	}
}

int	checkerb(t_lst **b)
{
	t_lst	*temp;
	t_lst	*temp2;

	temp = *b;
	while (temp->next)
	{
		temp2 = temp->next;
		if (temp->content < temp2->content)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	ft_medianb(t_lst **b, int buf)
{
	int		median;
	int		count;
	int		temp;
	t_lst	*temp1;
	t_lst	*temp2;

	temp1 = *b;
	while (temp1)
	{
		count = 0;
		temp = buf;
		temp2 = *b;
		median = temp1->content;
		while (temp2 && temp-- > 0)
		{
			if (temp2->content > median)
				count++;
			temp2 = temp2->next;
		}
		if (count == (buf / 2))
			return (median);
		temp1 = temp1->next;
	}
	return (0);
}

void	solverb(t_lst **b, t_lst **a, int buf)
{
	int		median;
	t_lst	*temp;
	int		tsize;

	temp = *b;
	tsize = lstsize(a) + lstsize(b);
	if (lstsize(b) == 1 || checkerb(b) == 1)
		return ;
	if (buf > tsize / 2)
		buf = lstsize(b);
	median = ft_medianb(&temp, buf);
	rlstsplit(&temp, a, median, buf);
	twosort(a, &temp);
	*b = temp;
}
