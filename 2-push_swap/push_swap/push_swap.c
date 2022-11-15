/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 15:42:53 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/15 15:54:07 by kali          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "push_swap.h"
#include <limits.h>

void	parser(t_lst **a, char **s, int ac)
{
	char	**arr;
	int		i;
	t_lst	*temp;

	i = -1;
	arr = NULL;
	temp = NULL;
	if (ac == 2)
	{
		arr = ft_split(s[1], ' ');
		singlecase(arr);
		arroverflow(arr);
		while (arr[++i])
		{
			temp = ft_lnew(ft_atoi(arr[i]));
			ft_ladd_end(a, temp);
		}
		freesplit(arr);
		ft_dupcheck(a);
		return ;
	}
	parser2(a, s, ac);
}

void	parser2(t_lst **a, char **s, int ac)
{
	int		i;
	t_lst	*temp;

	i = 1;
	temp = NULL;
	while (i < ac)
	{
		if (s[i][0] == ' ' || ft_atoi(s[i]) > INT_MAX
			|| ft_atoi(s[i]) < INT_MIN)
			ft_error();
		temp = ft_lnew(ft_atoi(s[i]));
		ft_ladd_end(a, temp);
		i++;
	}
	ft_dupcheck(a);
}

void	inputcheck(char **s, int ac)
{
	int		i;
	int		j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (s[i][0] == 0)
			ft_error();
		while (s[i][j])
		{
			if ((s[i][j] >= '0' && s[i][j] <= '9') ||
				s[i][j] == ' ' || s[i][j] == '-' || s[i][j] == '+')
				j++;
			else
				ft_error();
		}
		i++;
	}
}

int	checkera(t_lst **a)
{
	t_lst	*temp;
	t_lst	*temp2;

	temp = *a;
	while (temp->next)
	{
		temp2 = temp->next;
		if (temp->content > temp2->content)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_lst	*a;
	t_lst	*b;
	t_lst	*temp;

	a = NULL;
	b = NULL;
	if (ac < 2)
		exit(EXIT_SUCCESS);
	inputcheck(av, ac);
	parser(&a, av, ac);
	if (lstsize(&a) <= 5 && checkera(&a) == 0)
		fivesort(&a, &b);
	twosort(&a, &b);
	threesort(&a, &b);
	while (checkera(&a) == 0 || lstsize(&b) != 0)
		supersolver(&a, &b);
	while (a)
	{
		temp = a;
		a = a->next;
		free(temp);
	}
	exit(EXIT_SUCCESS);
}
