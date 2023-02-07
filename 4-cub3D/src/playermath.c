/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   playermath.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/31 16:33:11 by pdong         #+#    #+#                 */
/*   Updated: 2023/01/31 21:41:59 by paulniezen    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	fancy_wall_chk(t_data *data, double dx, double dy)
{
	if (dx >= 0 && dy >= 0)
		return (wallcheck(data, 0.25, 0) && wallcheck(data, 0, 0.25));
	else if (dx >= 0 && dy < 0)
		return (wallcheck(data, 0.25, 0) && wallcheck(data, 0, -0.25));
	else if (dx < 0 && dy >= 0)
		return (wallcheck(data, -0.25, 0) && wallcheck(data, 0, 0.25));
	else
		return (wallcheck(data, -0.25, 0) && wallcheck(data, 0, -0.25));
}

void	update_w(t_data *data)
{
	double	dx;
	double	dy;

	dx = (PLAYER_SPEED / (double)(TILE_SIZE)) * cos(data->player.angle);
	dy = (-PLAYER_SPEED / (double)(TILE_SIZE)) * sin(data->player.angle);
	if (fancy_wall_chk(data, dx, dy))
	{
		data->player.x += dx;
		data->player.y += dy;
	}
}

void	update_s(t_data *data)
{
	double	dx;
	double	dy;

	dx = (-PLAYER_SPEED / (double)(TILE_SIZE)) * cos(data->player.angle);
	dy = (PLAYER_SPEED / (double)(TILE_SIZE)) * sin(data->player.angle);
	if (fancy_wall_chk(data, dx, dy))
	{
		data->player.x += dx;
		data->player.y += dy;
	}
}

void	update_a(t_data *data)
{
	double	dx;
	double	dy;

	dx = (-PLAYER_SPEED / (double)(TILE_SIZE)) * sin(data->player.angle);
	dy = (-PLAYER_SPEED / (double)(TILE_SIZE)) * cos(data->player.angle);
	if (fancy_wall_chk(data, dx, dy))
	{
		data->player.x += dx;
		data->player.y += dy;
	}
}

void	update_d(t_data *data)
{
	double	dx;
	double	dy;

	dx = (PLAYER_SPEED / (double)(TILE_SIZE)) * sin(data->player.angle);
	dy = (PLAYER_SPEED / (double)(TILE_SIZE)) * cos(data->player.angle);
	if (fancy_wall_chk(data, dx, dy))
	{
		data->player.x += dx;
		data->player.y += dy;
	}
}
