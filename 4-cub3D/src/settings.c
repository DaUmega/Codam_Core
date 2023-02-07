/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   settings.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: paulniezen <paulniezen@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 14:52:09 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/01/27 15:03:18 by paulniezen    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <math.h>

double	fov(void)
{
	return (M_PI / 3);
}

double	half_fov(void)
{
	return (fov() / 2);
}

double	num_rays(void)
{
	return (floor(WINDOW_WIDTH / 2));
}

double	half_num_rays(void)
{
	return (floor(num_rays() / 2));
}

double	delta_angle(void)
{
	return (fov() / num_rays());
}
