/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 10:04:43 by pdong         #+#    #+#                 */
/*   Updated: 2023/06/17 19:20:50 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sky.h"

int	is_valid(int input[SI], int grid[SI][SI], int row, int col)
{
	if (!check_horizontal_left(input, grid, row, col)
		|| !check_horizontal_right(input, grid, row, col)
		|| !check_vertical_bottom(input, grid, row, col)
		|| !check_vertical_top(input, grid, row, col))
		return (0);
	return (1);
}

int	is_solved(int input[SI], int grid[SI][SI], int row, int col)
{
	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			if (!is_valid(input, grid, row, col))
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

int	solve(int input[SI], int grid[SI][SI], int row, int col)
{
	int	i;

	i = 1;
	if (col >= 4)
	{
		col = 0;
		row++;
	}
	if (row >= 4)
		return (is_solved(input, grid, 0, 0));
	while (i <= 4)
	{
		grid[row][col] = i;
		if (check_dup(grid, row, col))
		{
			if (solve(input, grid, row, col + 1))
				return (is_valid(input, grid, row, col));
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
	while (i < 4)
	{
		j = 0;
		while (j < 4)
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
	int	input[16];
	int	ans[SI][SI];

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
