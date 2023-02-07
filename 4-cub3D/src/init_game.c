/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: paulniezen <paulniezen@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 12:10:33 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/02/01 16:09:02 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	fill_image(mlx_image_t *img, t_rgb rgb_color)
{
	int	color;
	int	x;
	int	y;

	ft_bzero(img->pixels,
		img->width * img->height * sizeof(int));
	color = rgb_to_int(rgb_color);
	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

static mlx_image_t	*create_background_image(mlx_t *mlx, uint32_t width,
	uint32_t height, t_rgb color)
{
	mlx_image_t	*image;

	image = mlx_new_image(mlx, width, height);
	if (!image)
		ft_error(NULL, "Failed to create background image.");
	fill_image(image, color);
	return (image);
}

static void	init_main_images(t_data *data, t_images *images)
{
	images->ceiling = create_background_image(data->mlx, data->mlx->width,
			data->mlx->height, data->f_color);
	images->floor = create_background_image(data->mlx, data->mlx->width,
			data->mlx->height / 2, data->c_color);
	mlx_image_to_window(data->mlx, images->ceiling, 0, 0);
	mlx_image_to_window(data->mlx, images->floor, 0, 0);
	images->walls = mlx_new_image(data->mlx,
			data->mlx->width, data->mlx->height);
}

void	start(t_data *data)
{
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
	if (!data->mlx)
		ft_error(data, "Could not init MLX instance.");
	init_main_images(data, &data->images);
	data->images.walls = mlx_new_image(data->mlx,
			data->mlx->width, data->mlx->height);
	mlx_image_to_window(data->mlx, data->images.walls, 0, 0);
	init_minimap(data);
	data->images.rays = mlx_new_image(data->mlx,
			data->images.mini_map->width, data->images.mini_map->height);
	mlx_image_to_window(data->mlx, data->images.rays, 0, 0);
	if (!mlx_loop_hook(data->mlx, key_hooks, data))
		ft_error(data, "Keys loop_hook error.");
	mlx_resize_hook(data->mlx, resize_screen, data);
	mlx_close_hook(data->mlx, exit_program, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
