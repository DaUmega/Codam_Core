/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operation.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 21:05:06 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/14 21:05:07 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

void	ft_swap(t_lst **a)
{
	t_lst	*temp1;
	t_lst	*temp2;
	t_lst	*temp3;

	if (!a || !*a)
		return ;
	temp1 = *a;
	temp2 = temp1->next;
	temp3 = temp2->next;
	temp2->prev = NULL;
	temp2->next = temp1;
	temp1->prev = temp2;
	temp1->next = temp3;
	if (temp3)
		temp3->prev = temp1;
	*a = temp2;
}

void	ft_push(t_lst **a, t_lst **b)
{
	t_lst	*atop;
	t_lst	*tempa;

	if (!a || !*a)
		return ;
	atop = *a;
	tempa = atop;
	atop = atop->next;
	tempa->next = NULL;
	tempa->prev = NULL;
	ft_ladd_start(b, tempa);
	if (atop)
	{
		atop->prev = NULL;
		*a = atop;
	}
	else
		*a = NULL;
}

void	ft_rotate(t_lst **a)
{
	t_lst	*atop;
	t_lst	*abot;
	t_lst	*temp1;

	atop = *a;
	if (!atop->next)
		return ;
	temp1 = *a;
	while (temp1)
	{
		abot = temp1;
		temp1 = temp1->next;
	}
	temp1 = *a;
	atop = atop->next;
	atop->prev = NULL;
	abot->next = temp1;
	temp1->prev = abot;
	temp1->next = NULL;
	*a = atop;
}

void	ft_rrotate(t_lst **a)
{
	t_lst	*atop;
	t_lst	*abot;
	t_lst	*temp1;

	atop = *a;
	if (!atop->next)
		return ;
	temp1 = *a;
	while (temp1)
	{
		abot = temp1;
		temp1 = temp1->next;
	}
	temp1 = abot;
	temp1 = temp1->prev;
	temp1->next = NULL;
	abot->next = atop;
	abot->prev = NULL;
	atop->prev = abot;
	*a = abot;
}

int	num_sorted(t_lst **a, t_lst **b)
{
	t_lst	*temp;
	t_lst	*prev;
	int		i;

	temp = *a;
	i = 1;
	while (temp->next)
		temp = temp->next;
	while (temp->prev)
	{
		prev = temp->prev;
		while (prev->prev)
		{
			if (temp->content < prev->content)
				return (i - 1);
			prev = prev->prev;
		}
		temp = temp->prev;
		i++;
	}
	i = num_sorted2(b, temp->content, i);
	return (i);
}
