/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gridcheck.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 10:17:13 by pdong         #+#    #+#                 */
/*   Updated: 2023/06/17 18:52:50 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sky.h"

int	check_dup(int grid[SI][SI], int row, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (i != col && grid[row][i] == grid[row][col])
			return (0);
		i++;
	}
	i = 0;
	while (i < row)
	{
		if (i != row && grid[i][col] == grid[row][col])
			return (0);
		i++;
	}
	return (1);
}

int	check_horizontal_right(int *input, int grid[SI][SI], int row, int col)
{
	int	i;
	int	visible;
	int	max;

	i = 3;
	visible = 1;
	max = grid[row][3];
	while (i >= 0)
	{
		if (grid[row][i] != 0 && grid[row][i] > max)
		{
			visible++;
			max = grid[row][i];
		}
		i--;
	}
	return (visible == input[row + 12]);
}

int	check_horizontal_left(int *input, int grid[SI][SI], int row, int col)
{
	int	i;
	int	visible;
	int	max;

	i = 0;
	visible = 1;
	max = grid[row][0];
	while (i <= 3)
	{
		if (grid[row][i] != 0 && grid[row][i] > max)
		{
			visible++;
			max = grid[row][i];
		}
		i++;
	}
	return (visible == input[row + 8]);
}

int	check_vertical_bottom(int *input, int grid[SI][SI], int row, int col)
{
	int	i;
	int	visible;
	int	max;

	i = 3;
	visible = 1;
	max = grid[3][col];
	while (i >= 0)
	{
		if (grid[i][col] != 0 && grid[i][col] > max)
		{
			visible++;
			max = grid[i][col];
		}
		i--;
	}
	return (visible == input[col + 4]);
}

int	check_vertical_top(int *input, int grid[SI][SI], int row, int col)
{
	int	i;
	int	visible;
	int	max;

	i = 0;
	visible = 1;
	max = grid[0][col];
	while (i <= 3)
	{
		if (grid[i][col] != 0 && grid[i][col] > max)
		{
			visible++;
			max = grid[i][col];
		}
		i++;
	}
	return (visible == input[col]);
}
