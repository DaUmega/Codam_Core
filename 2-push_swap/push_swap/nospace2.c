/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nospace2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 15:42:21 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/15 16:02:00 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"
#include <limits.h>

void	singlecase(char **arr)
{
	if (ft_atoi(arr[0]) > INT_MAX || ft_atoi(arr[0]) < INT_MIN)
		ft_error();
	if (!arr[1] && ft_atoi(arr[0]) <= INT_MAX && ft_atoi(arr[0]) >= INT_MIN)
	{
		freesplit(arr);
		exit(EXIT_SUCCESS);
	}
}

void	ft_dupcheck(t_lst **a)
{
	t_lst	*temp1;
	t_lst	*temp2;
	int		content;
	int		chk;

	temp1 = *a;
	while (temp1)
	{
		content = temp1->content;
		temp2 = *a;
		chk = 0;
		while (temp2)
		{
			if (content == temp2->content)
				chk++;
			temp2 = temp2->next;
		}
		if (chk != 1)
			ft_error();
		temp1 = temp1->next;
	}
}

void	arroverflow(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_atoi(arr[i]) > INT_MAX || ft_atoi(arr[i]) < INT_MIN)
		{
			freesplit(arr);
			ft_error();
		}
		i++;
	}
}
