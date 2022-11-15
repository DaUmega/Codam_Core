/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nospace.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 15:42:43 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/15 15:42:44 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"
#include <limits.h>

int	num_sorted2(t_lst **b, int content, int i)
{
	t_lst	*tempb;

	tempb = *b;
	while (tempb)
	{
		if (content < tempb->content)
			return (i - 1);
		tempb = tempb->next;
	}
	return (i);
}

void	supersolver(t_lst **a, t_lst **b)
{
	int	i;
	int	j;

	j = num_sorted(a, b);
	solvera(a, b, j + 3);
	if (b)
		solverb(b, a, j);
	if (checkera(a) == 1 && lstsize(b) == 0)
		exit(EXIT_SUCCESS);
	if (checkera(a) == 1 && checkerb(b) == 1)
	{
		i = lstsize(b);
		while (i--)
		{
			ft_push(b, a);
			ft_printf("pa\n");
		}
	}
}

void	pushnsortb(t_lst **a, t_lst **b)
{
	ft_push(b, a);
	ft_printf("pa\n");
	twosort(a, b);
}

int	getindexb(t_lst **b, int j)
{
	t_lst	*temp;
	int		index;

	temp = *b;
	index = 0;
	while (temp)
	{
		if (temp->content == j)
			break ;
		index++;
		temp = temp->next;
	}
	return (index);
}

void	freesplit(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
