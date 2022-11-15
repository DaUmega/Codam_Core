/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   algoa.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 21:04:30 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/15 15:24:32 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

int	ft_mediana(t_lst **a, int buf)
{
	int		median;
	int		count;
	int		temp;
	t_lst	*temp1;
	t_lst	*temp2;

	temp1 = *a;
	temp = 0;
	while (temp1)
	{
		count = 0;
		temp = lstsize(a);
		temp2 = *a;
		median = temp1->content;
		while (temp2 && temp-- > buf)
		{
			if (temp2->content < median)
				count++;
			temp2 = temp2->next;
		}
		if (count == (lstsize(a) - buf) / 3)
			return (median);
		temp1 = temp1->next;
	}
	return (0);
}

void	threesort(t_lst **a, t_lst **b)
{
	int		sizea;
	int		sizeb;

	if (!a || !*a)
		return ;
	sizea = lstsize(a);
	sizeb = lstsize(b);
	if (sizea > 2 && sizeb > 2)
		checkthirdab(a, b);
	if (sizea > 2)
		checkthirda(a, b);
	if (sizeb > 2)
		checkthirdb(a, b);
}

void	lstsplit(t_lst **a, t_lst **b, int median, int buf)
{
	t_lst	*temp;
	int		i;
	int		j;

	temp = *a;
	i = (lstsize(a) - buf) / 3;
	j = 0;
	while (i > 0)
	{
		if (temp->content < median)
		{
			ft_push(a, b);
			ft_printf("pb\n");
			twosort(a, b);
			i--;
		}
		else
		{
			ft_rotate(a);
			ft_printf("ra\n");
			j++;
		}
		temp = *a;
	}
	lstsplit2(a, j, buf);
}

void	lstsplit2(t_lst **a, int j, int buf)
{
	if (buf != 0)
	{
		while (j--)
		{
			ft_rrotate(a);
			ft_printf("rra\n");
		}
	}
}

void	solvera(t_lst **a, t_lst **b, int buf)
{
	int		i;
	int		median;
	t_lst	*temp;

	twosort(a, b);
	threesort(a, b);
	temp = *a;
	i = lstsize(&temp);
	if (i == 1)
		return ;
	while (i > buf)
	{
		median = ft_mediana(&temp, buf - 3);
		lstsplit(&temp, b, median, buf - 3);
		i = lstsize(&temp);
		twosort(&temp, b);
		threesort(&temp, b);
		if (lstsize(&temp) <= 5)
			fivesort(&temp, b);
		*a = temp;
	}
}
