/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: paulniezen <paulniezen@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 18:36:11 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/02/01 19:25:08 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_square(t_data *data, float x, float y, long color)
{
	float	x_start;
	float	y_start;
	float	scale;

	x_start = x;
	y_start = y;
	scale = get_scale(data);
	while (y < y_start + (scale * TILE_SIZE))
	{
		x = x_start;
		while (x < x_start + (scale * TILE_SIZE))
		{
			mlx_put_pixel(data->images.mini_map, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_mini_map(t_data *data, char **map, float scale)
{
	int		x;
	int		y;
	float	step_x;
	float	step_y;

	y = 0;
	step_y = 0;
	while (y < data->height)
	{
		x = 0;
		step_x = 0;
		while (x < data->length)
		{
			if (map[y][x] == '1')
				draw_square(data, step_x, step_y, BLACK);
			step_x += (scale * TILE_SIZE);
			x++;
		}
		step_y += (scale * TILE_SIZE);
		y++;
	}
}

void	cast_ray(t_data *data)
{
	double	angle_l;
	double	angle_r;
	double	inc;
	t_rc	coor;
	float	scale;

	scale = get_scale(data);
	ft_bzero(data->images.rays->pixels,
		data->images.rays->width * data->images.rays->height * sizeof(int));
	angle_l = data->player.angle + M_PI / 6;
	angle_r = data->player.angle - M_PI / 6;
	inc = (angle_l - angle_r) / 200;
	while (angle_r < angle_l)
	{
		coor.s_x = data->player.x * TILE_SIZE * scale + 1;
		coor.s_y = data->player.y * TILE_SIZE * scale + 1;
		coor.e_x = ray_final_x(data, angle_r) * TILE_SIZE * scale + 1;
		coor.e_y = ray_final_y(data, angle_r) * TILE_SIZE * scale + 1;
		bresenham(data, data->images.rays, coor, true);
		angle_r += inc;
	}
}
