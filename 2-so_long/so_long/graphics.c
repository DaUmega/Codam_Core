/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 16:56:15 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/24 18:18:17 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

void	init_imgs(void)
{
	mlx_texture_t	*temp;

	temp = mlx_load_png("img/bunnyw.png");
	g_bunnyw = mlx_texture_to_image(g_mlx, temp);
	mlx_delete_texture(temp);
	temp = mlx_load_png("img/bunnya.png");
	g_bunnya = mlx_texture_to_image(g_mlx, temp);
	mlx_delete_texture(temp);
	temp = mlx_load_png("img/bunnys.png");
	g_bunnys = mlx_texture_to_image(g_mlx, temp);
	mlx_delete_texture(temp);
	temp = mlx_load_png("img/bunnyd.png");
	g_bunnyd = mlx_texture_to_image(g_mlx, temp);
	mlx_delete_texture(temp);
}

void	init_imgs2(void)
{
	mlx_texture_t	*temp;

	temp = mlx_load_png("img/wall.png");
	g_wall = mlx_texture_to_image(g_mlx, temp);
	mlx_delete_texture(temp);
	temp = mlx_load_png("img/knight.png");
	g_knight = mlx_texture_to_image(g_mlx, temp);
	mlx_delete_texture(temp);
	temp = mlx_load_png("img/grass.png");
	g_grass = mlx_texture_to_image(g_mlx, temp);
	mlx_delete_texture(temp);
	temp = mlx_load_png("img/exit.png");
	g_hole = mlx_texture_to_image(g_mlx, temp);
	mlx_delete_texture(temp);
}

void	showmap(int a)
{
	int	i;
	int	j;

	i = 0;
	clearoldmap();
	while (g_data->map[i])
	{
		j = 0;
		while (g_data->map[i][j])
		{
			if (g_data->map[i][j] == '1')
				mlx_image_to_window(g_mlx, g_wall, j * 32, i * 32);
			if (g_data->map[i][j] == '0')
				mlx_image_to_window(g_mlx, g_grass, j * 32, i * 32);
			if (g_data->map[i][j] == 'C')
				mlx_image_to_window(g_mlx, g_knight, j * 32, i * 32);
			if (g_data->map[i][j] == 'E')
				mlx_image_to_window(g_mlx, g_hole, j * 32, i * 32);
			if (g_data->map[i][j] == 'P')
				showplayer(a);
			j++;
		}
		i++;
	}
}

int32_t	graphics(void)
{
	xpm_t	*xpm;

	xpm = NULL;
	g_mlx = mlx_init(g_data->length * 32,
			g_data->height * 32, "The Bunny", true);
	if (!g_mlx)
		exit(EXIT_FAILURE);
	init_imgs();
	init_imgs2();
	showmap(4);
	mlx_key_hook(g_mlx, &my_keyhook, NULL);
	mlx_loop(g_mlx);
	mlx_terminate(g_mlx);
	return (EXIT_SUCCESS);
}
