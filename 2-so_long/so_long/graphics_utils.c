/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   graphics_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 16:52:07 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/25 18:09:09 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

void	showplayer(int i)
{
	if (i == 1)
	{
		mlx_image_to_window(g_mlx, g_bunnyw, g_data->player_x * 32,
			g_data->player_y * 32);
	}
	if (i == 2)
	{
		mlx_image_to_window(g_mlx, g_bunnys, g_data->player_x * 32,
			g_data->player_y * 32);
	}
	if (i == 3)
	{
		mlx_image_to_window(g_mlx, g_bunnya, g_data->player_x * 32,
			g_data->player_y * 32);
	}
	if (i == 4)
	{
		mlx_image_to_window(g_mlx, g_bunnyd, g_data->player_x * 32,
			g_data->player_y * 32);
	}
}

void	obscheckws(int i)
{
	if (g_data->map[g_data->player_y + i][g_data->player_x] == '0')
	{
		g_data->map[g_data->player_y][g_data->player_x] = '0';
		g_data->map[g_data->player_y + i][g_data->player_x] = 'P';
		g_data->player_y += i;
		g_data->steps++;
	}
	else if (g_data->map[g_data->player_y + i][g_data->player_x] == 'C')
	{
		g_data->map[g_data->player_y][g_data->player_x] = '0';
		g_data->map[g_data->player_y + i][g_data->player_x] = 'P';
		g_data->player_y += i;
		g_data->c_count--;
		g_data->steps++;
	}
	else if (g_data->map[g_data->player_y + i][g_data->player_x] == 'E')
	{
		if (g_data->c_count == 0)
			mlx_close_window(g_mlx);
	}
	ft_printf("Steps Taken: %d\n", g_data->steps);
}

void	obscheckad(int i)
{
	if (g_data->map[g_data->player_y][g_data->player_x + i] == '0')
	{
		g_data->map[g_data->player_y][g_data->player_x] = '0';
		g_data->map[g_data->player_y][g_data->player_x + i] = 'P';
		g_data->player_x += i;
		g_data->steps++;
	}
	else if (g_data->map[g_data->player_y][g_data->player_x + i] == 'C')
	{
		g_data->map[g_data->player_y][g_data->player_x] = '0';
		g_data->map[g_data->player_y][g_data->player_x + i] = 'P';
		g_data->player_x += i;
		g_data->c_count--;
		g_data->steps++;
	}
	else if (g_data->map[g_data->player_y][g_data->player_x + i] == 'E')
	{
		if (g_data->c_count == 0)
		{
			mlx_close_window(g_mlx);
			g_data->steps++;
		}
	}
	ft_printf("Steps Taken: %d\n", g_data->steps);
}

void	clearoldmap(void)
{
	mlx_delete_image(g_mlx, g_bunnyw);
	mlx_delete_image(g_mlx, g_bunnya);
	mlx_delete_image(g_mlx, g_bunnys);
	mlx_delete_image(g_mlx, g_bunnyd);
	mlx_delete_image(g_mlx, g_grass);
	mlx_delete_image(g_mlx, g_knight);
	mlx_delete_image(g_mlx, g_wall);
	mlx_delete_image(g_mlx, g_hole);
	init_imgs();
	init_imgs2();
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	param = NULL;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		obscheckws(-1);
		showmap(1);
	}
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		obscheckws(1);
		showmap(2);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		obscheckad(-1);
		showmap(3);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		obscheckad(1);
		showmap(4);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(g_mlx);
}
