/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 11:57:12 by pdong         #+#    #+#                 */
/*   Updated: 2023/06/17 18:52:57 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sky.h"

int	input_check(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] >= '1' && s[i] <= '4')
			count++;
		i++;
	}
	return (count == 4 * SI);
}

void	parse_input(char *s, int *ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s && s[i])
	{
		if (s[i] >= '1' && s[i] <= '4')
		{
			ret[j] = s[i] - '0';
			j++;
		}
		i++;
	}
}

void	initialize(int ans[SI][SI])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ans[i][j] = 0;
			j++;
		}
		i++;
	}
}
