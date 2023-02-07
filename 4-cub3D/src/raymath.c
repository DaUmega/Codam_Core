/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raymath.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/29 13:14:46 by kali          #+#    #+#                 */
/*   Updated: 2023/01/31 16:46:58 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static double	set_dx_dy(double c_angle)
{
	if (c_angle > 0)
		return (1);
	else
		return (-1);
}

static double	ray_hit_x(t_data *data, double angle)
{
	double	nx;
	double	ny;
	double	dist;
	double	dx;

	if (fabs(cos(angle)) < 0.01)
		return (9999999);
	if (cos(angle) > 0)
		nx = ceil(data->player.x + 0.00001);
	else
		nx = floor(data->player.x);
	dx = set_dx_dy(cos(angle));
	dist = fabs((nx - data->player.x) / cos(angle));
	ny = dist * sin(angle) * -1;
	while (wallcheck(data, dx, ny))
	{
		dx += set_dx_dy(cos(angle));
		dist += fabs(set_dx_dy(cos(angle)) / cos(angle));
		ny = dist * sin(angle) * -1;
	}
	return (dist);
}

static double	ray_hit_y(t_data *data, double angle)
{
	double	nx;
	double	ny;
	double	dist;
	double	dy;

	if (fabs(sin(angle)) < 0.01)
		return (9999999);
	if (sin(angle) < 0)
		ny = ceil(data->player.y + 0.00001);
	else
		ny = floor(data->player.y);
	dy = set_dx_dy(sin(angle)) * -1;
	dist = fabs((ny - data->player.y) / sin(angle));
	nx = dist * cos(angle);
	while (wallcheck(data, nx, dy))
	{
		dy -= set_dx_dy(sin(angle));
		dist += fabs(set_dx_dy(sin(angle)) / sin(angle));
		nx = dist * cos(angle);
	}
	return (dist);
}

double	ray_final_x(t_data *data, double angle)
{
	double	dist;
	double	temp;

	dist = ray_hit_x(data, angle);
	temp = ray_hit_y(data, angle);
	if (temp <= dist)
		dist = temp;
	return (dist * cos(angle) + data->player.x);
}

double	ray_final_y(t_data *data, double angle)
{
	double	dist;
	double	temp;

	dist = ray_hit_x(data, angle);
	temp = ray_hit_y(data, angle);
	if (temp <= dist)
		dist = temp;
	return (dist * sin(angle) * -1 + data->player.y);
}
