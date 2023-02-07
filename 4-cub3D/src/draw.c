/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 08:42:43 by pniezen       #+#    #+#                 */
/*   Updated: 2023/02/01 20:53:58 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

mlx_texture_t	*texture_pick(t_data *data, t_rc coor)
{
	if (coor.e2_x > coor.s2_x)
	{
		if (coor.e2_y > coor.s2_y && (fabs(coor.e2_x) > fabs(floor(coor.e2_x))))
			return (data->n_texture);
		else if (coor.e2_y < coor.s2_y
			&& (fabs(coor.e2_x) > fabs(floor(coor.e2_x))))
			return (data->s_texture);
		else
			return (data->w_texture);
	}
	else
	{
		if (coor.e2_y > coor.s2_y && (fabs(coor.e2_x) > fabs(floor(coor.e2_x))))
			return (data->n_texture);
		else if (coor.e2_y < coor.s2_y
			&& (fabs(coor.e2_x) > fabs(floor(coor.e2_x))))
			return (data->s_texture);
		else
			return (data->e_texture);
	}
}

uint32_t	pixel_find(t_data *data, t_rc coor, double cx, double cy)
{
	int				x;
	int				y;
	int				index;
	double			temp;
	mlx_texture_t	*pic;

	pic = texture_pick(data, coor);
	temp = 1.0 - (coor.e2_x - floor(coor.e2_x) + coor.e2_y - floor(coor.e2_y));
	x = 4 * (int)(floor(temp * pic->width));
	temp = sqrt(square(coor.s3_x - cx) + square(coor.s3_y - cy))
		/ sqrt(square(coor.e3_x - coor.s3_x) + square(coor.e3_y - coor.s3_y));
	y = (int)(floor(temp * pic->height));
	index = x + (y * 4 * pic->width);
	return (get_pixel_color(&pic->pixels[index]));
}

static void	pixel_print(t_data *data, mlx_image_t *img, t_rc coor,
	bool mini_map)
{
	if (mini_map)
	{
		if ((coor.s_x < data->mlx->width
				&& coor.s_y < data->mlx->height
				&& coor.s_y > 0 && coor.s_x > 0))
			mlx_put_pixel(img, coor.s_x, coor.s_y, WHITE);
		if ((coor.e_x < data->mlx->width
				&& coor.e_y < data->mlx->height
				&& coor.e_y > 0 && coor.e_x > 0))
			mlx_put_pixel(img, coor.e_x, coor.e_y, WHITE);
	}
	else
	{
		if ((coor.s_x < data->mlx->width
				&& coor.s_y < data->mlx->height
				&& coor.s_y > 0 && coor.s_x > 0))
			mlx_put_pixel(img, coor.s_x, coor.s_y,
				pixel_find(data, coor, coor.s_x, coor.s_y));
		if ((coor.e_x < data->mlx->width
				&& coor.e_y < data->mlx->height
				&& coor.e_y > 0 && coor.e_x > 0))
			mlx_put_pixel(img, coor.e_x, coor.e_y,
				pixel_find(data, coor, coor.e_x, coor.e_y));
	}
}

void	bresenham(t_data *data, mlx_image_t *img, t_rc coor, bool mini_map)
{
	float	max;
	float	x_step;
	float	y_step;

	x_step = coor.e_x - coor.s_x;
	y_step = coor.e_y - coor.s_y;
	max = fmax(fabs(x_step), fabs(y_step));
	x_step /= max;
	y_step /= max;
	while (true)
	{
		pixel_print(data, img, coor, mini_map);
		if (!(int)(coor.e_x - coor.s_x) && !(int)(coor.e_y - coor.s_y))
			break ;
		coor.s_x += x_step;
		coor.s_y += y_step;
	}
}
