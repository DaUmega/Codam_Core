/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 10:04:43 by pdong         #+#    #+#                 */
/*   Updated: 2023/08/01 15:07:14 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sky.h"

void	print_answer(int ans[SI][SI])
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < SI)
	{
		j = 0;
		while (j < SI)
		{
			c = ans[i][j] + '0';
			write(1, &c, 1);
			if (j < SI - 1)
				write(1, " ", 1);
			j++;
		}
		i++;
		write(1, "\n", 1);
	}
}

int	main(int ac, char **av)
{
	int		input[SI * 4];
	int		ans[SI][SI];

	write(1, "Usage: ./rush01 \"up down left right\"\n", 37);
	if (ac != 2 || !input_check(av[1]))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	initialize(ans);
	parse_input(av[1], input);
	if (solve(input, ans, 0, 0))
		print_answer(ans);
	else
		write(1, "Error\n", 6);
	return (0);
}
