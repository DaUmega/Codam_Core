/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 10:04:43 by pdong         #+#    #+#                 */
/*   Updated: 2023/07/25 18:43:48 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sky.h"

int	is_valid(int *input, int grid[SI][SI], int row, int col)
{
	return (check_dup(grid, row, col)
		&& check_horizontal_left(input, grid, row)
		&& check_horizontal_right(input, grid, row)
		&& check_vertical_bottom(input, grid, col)
		&& check_vertical_top(input, grid, col));
}

int	solve(int *input, int grid[SI][SI], int row, int col)
{
	int	i;

	i = 1;
	if (col >= SI)
	{
		col = 0;
		row++;
	}
	if (row >= SI)
		return (1);
	while (i <= SI)
	{
		grid[row][col] = i;
		if (is_valid(input, grid, row, col))
		{
			if (solve(input, grid, row, col + 1))
				return (1);
		}
		i++;
	}
	grid[row][col] = 0;
	return (0);
}

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
