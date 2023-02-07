/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   walls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: paulniezen <paulniezen@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 12:04:06 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/02/06 13:53:45 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <math.h>

double	square(double a)
{
	return (a * a);
}

void	copy_coords(t_rc *coor)
{
	coor->s2_x = coor->s_x / TILE_SIZE;
	coor->s2_y = coor->s_y / TILE_SIZE;
	coor->e2_x = coor->e_x / TILE_SIZE;
	coor->e2_y = coor->e_y / TILE_SIZE;
}

static void	bresenwall(t_data *data, t_rc coor, double angle)
{
	double	height;
	double	x;

	copy_coords(&coor);
	height = 1.0 / (sqrt(square((coor.e_x - coor.s_x) / TILE_SIZE)
				+ square((coor.e_y - coor.s_y) / TILE_SIZE))
			+ 0.00001) / cos(data->player.angle - angle) * data->mlx->height;
	coor.s3_y = data->mlx->height / 2 - (height / 2);
	coor.e3_y = data->mlx->height / 2 + (height / 2);
	x = data->mlx->width * (0.5 + (data->player.angle - angle) / (M_PI / 3));
	coor.s3_x = x;
	coor.e3_x = x;
	coor.s_y = coor.s3_y;
	coor.e_y = coor.e3_y;
	coor.s_x = coor.s3_x;
	coor.e_x = coor.e3_x;
	bresenham(data, data->images.walls, coor, false);
}

void	build_wall(t_data *data)
{
	double	angle_l;
	double	angle_r;
	double	inc;
	t_rc	coor;

	ft_bzero(data->images.walls->pixels,
		data->images.walls->width * data->images.walls->height * sizeof(int));
	angle_l = data->player.angle + M_PI / 6;
	angle_r = data->player.angle - M_PI / 6;
	inc = (angle_l - angle_r) / data->mlx->width;
	while (angle_r < angle_l)
	{
		coor.s_x = data->player.x * TILE_SIZE;
		coor.s_y = data->player.y * TILE_SIZE;
		coor.e_x = ray_final_x(data, angle_r) * TILE_SIZE;
		coor.e_y = ray_final_y(data, angle_r) * TILE_SIZE;
		bresenwall(data, coor, angle_r);
		angle_r += inc;
	}
}
