/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: paulniezen <paulniezen@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 18:39:20 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/02/01 10:28:25 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

float	get_scale(t_data *data)
{
	float	new_tilesize;

	if (data->length > data->height)
		new_tilesize = (WINDOW_WIDTH * MINI_SCALE) / data->length;
	else
		new_tilesize = (WINDOW_HEIGHT * MINI_SCALE) / data->height;
	return (new_tilesize / TILE_SIZE);
}

void	init_minimap(t_data *data)
{
	data->images.mini_map = mlx_new_image(data->mlx,
			data->length * TILE_SIZE * get_scale(data) + 1,
			data->height * TILE_SIZE * get_scale(data) + 1);
	draw_mini_map(data, data->map, get_scale(data));
	mlx_image_to_window(data->mlx, data->images.mini_map, 0, 0);
}
