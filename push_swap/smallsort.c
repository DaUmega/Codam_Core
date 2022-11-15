/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   smallsort.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 21:05:27 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/14 21:05:28 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

void	twosortab(t_lst **a, t_lst **b)
{
	t_lst	*firsta;
	t_lst	*seconda;
	t_lst	*firstb;
	t_lst	*secondb;

	firsta = *a;
	seconda = firsta->next;
	firstb = *b;
	secondb = firstb->next;
	if ((firsta->content > seconda->content)
		&& (firstb->content < secondb->content))
	{
		ft_swap(a);
		ft_swap(b);
		ft_printf("ss\n");
	}
	else if (firstb->content < secondb->content)
	{
		ft_swap(b);
		ft_printf("sb\n");
	}
}

void	twosort(t_lst **a, t_lst **b)
{
	t_lst	*firsta;
	t_lst	*seconda;

	if (!a || !*a)
		return ;
	firsta = *a;
	seconda = firsta->next;
	if (lstsize(b) > 1)
		twosortab(a, b);
	firsta = *a;
	seconda = firsta->next;
	if (firsta->content > seconda->content)
	{
		ft_swap(a);
		ft_printf("sa\n");
	}
}

void	checkthirdab(t_lst **a, t_lst **b)
{
	t_lst	*seconda;
	t_lst	*thirda;
	t_lst	*secondb;
	t_lst	*thirdb;

	seconda = *a;
	seconda = seconda->next;
	thirda = seconda->next;
	secondb = *b;
	secondb = secondb->next;
	thirdb = secondb->next;
	if (seconda->content > thirda->content
		&& secondb->content < thirdb->content)
	{
		ft_rotate(a);
		ft_rotate(b);
		ft_printf("rr\n");
		twosort(a, b);
		ft_rrotate(a);
		ft_rrotate(b);
		ft_printf("rrr\n");
		twosort(a, b);
	}
}

void	checkthirda(t_lst **a, t_lst **b)
{
	t_lst	*second;
	t_lst	*third;

	second = *a;
	second = second->next;
	third = second->next;
	if (lstsize(a) == 3 && second->content > third->content)
	{
		ft_rrotate(a);
		ft_printf("rra\n");
		twosort(a, b);
	}
	else if (second->content > third->content)
	{
		ft_rotate(a);
		ft_printf("ra\n");
		twosort(a, b);
		ft_rrotate(a);
		ft_printf("rra\n");
		twosort(a, b);
	}
}

void	checkthirdb(t_lst **a, t_lst **b)
{
	t_lst	*second;
	t_lst	*third;

	second = *b;
	second = second->next;
	third = second->next;
	if (lstsize(b) == 3 && second->content < third->content)
	{
		ft_rrotate(b);
		ft_printf("rrb\n");
		twosort(a, b);
	}
	else if (second->content < third->content)
	{
		ft_rotate(b);
		ft_printf("rb\n");
		twosort(a, b);
		ft_rrotate(b);
		ft_printf("rrb\n");
		twosort(a, b);
	}
}
