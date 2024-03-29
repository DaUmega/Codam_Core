/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gridcheck.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/17 10:17:13 by pdong         #+#    #+#                 */
/*   Updated: 2023/07/25 19:21:47 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "sky.h"

int	check_dup(int grid[SI][SI], int row, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (grid[row][i] == grid[row][col])
			return (0);
		i++;
	}
	i = 0;
	while (i < row)
	{
		if (grid[i][col] == grid[row][col])
			return (0);
		i++;
	}
	return (1);
}

int	check_horizontal_right(int *input, int grid[SI][SI], int row)
{
	int	i;
	int	visible;
	int	max;

	i = SI - 1;
	visible = 1;
	max = grid[row][i];
	if (max == 0)
		return (1);
	while (i >= 0)
	{
		if (grid[row][i] > max)
		{
			visible++;
			max = grid[row][i];
		}
		i--;
	}
	return (visible == input[row + SI * 3]);
}

int	check_horizontal_left(int *input, int grid[SI][SI], int row)
{
	int	i;
	int	visible;
	int	max;

	i = 0;
	visible = 1;
	max = grid[row][i];
	while (i <= SI - 1)
	{
		if (grid[row][i] == 0)
			return (visible <= input[row + SI * 2]);
		if (grid[row][i] > max)
		{
			visible++;
			max = grid[row][i];
		}
		i++;
	}
	if (i == SI)
		return (visible == input[row + SI * 2]);
	return (visible <= input[row + SI * 2]);
}

int	check_vertical_bottom(int *input, int grid[SI][SI], int col)
{
	int	i;
	int	visible;
	int	max;

	i = SI - 1;
	visible = 1;
	max = grid[i][col];
	if (max == 0)
		return (1);
	while (i >= 0)
	{
		if (grid[i][col] > max)
		{
			visible++;
			max = grid[i][col];
		}
		i--;
	}
	return (visible == input[col + SI]);
}

int	check_vertical_top(int *input, int grid[SI][SI], int col)
{
	int	i;
	int	visible;
	int	max;

	i = 0;
	visible = 1;
	max = grid[i][col];
	while (i <= SI - 1)
	{
		if (grid[i][col] == 0)
			return (visible <= input[col]);
		if (grid[i][col] > max)
		{
			visible++;
			max = grid[i][col];
		}
		i++;
	}
	if (i == SI)
		return (visible == input[col]);
	return (visible <= input[col]);
}
