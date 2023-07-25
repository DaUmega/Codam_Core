/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   algorithm.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 19:22:45 by pdong         #+#    #+#                 */
/*   Updated: 2023/07/25 19:48:06 by pdong         ########   odam.nl         */
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

int	branch_cut(int *input, int grid[SI][SI], int row, int col)
{
	if (row == 0 && grid[0][col] + input[col] > SI + 1)
		return (0);
	if (col == 0 && grid[row][0] + input[SI * 2 + row] > SI + 1)
		return (0);
	return (1);
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
		if (is_valid(input, grid, row, col) && branch_cut(input, grid, row, col))
		{
			if (solve(input, grid, row, col + 1))
				return (1);
		}
		i++;
	}
	grid[row][col] = 0;
	return (0);
}