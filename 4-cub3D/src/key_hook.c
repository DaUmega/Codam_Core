/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 12:14:37 by pniezen       #+#    #+#                 */
/*   Updated: 2023/02/01 08:59:04 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <math.h>

static void	view(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle += PLAYER_ROT_SPEED * data->mlx->delta_time;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle -= PLAYER_ROT_SPEED * data->mlx->delta_time;
}

bool	wallcheck(t_data *data, double dx, double dy)
{
	int	rdx;
	int	rdy;

	if (data->player.x + dx <= 0 || data->player.x + dx >= data->length - 1
		|| data->player.y + dy <= 0 || data->player.y + dy >= data->height - 1)
		return (0);
	rdx = (int)(floor(data->player.x + dx));
	rdy = (int)(floor(data->player.y + dy));
	return (data->map[rdy][rdx] != '1');
}

static void	player_move(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		update_w(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		update_s(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		update_a(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		update_d(data);
}

void	key_hooks(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit_program(data);
	player_move(data);
	view(data);
	build_wall(data);
	cast_ray(data);
}

void	resize_screen(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = param;
	data->mlx->width = width;
	data->mlx->height = height;
	mlx_resize_image(data->images.ceiling, width, height);
	fill_image(data->images.ceiling, data->f_color);
	mlx_resize_image(data->images.floor, width, height / 2);
	fill_image(data->images.floor, data->c_color);
	mlx_resize_image(data->images.walls, width, height);
}
