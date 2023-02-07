/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: paulniezen <paulniezen@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 13:38:06 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/02/01 15:15:28 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	rgb_to_int(t_rgb color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 255);
}

int	get_pixel_color(u_int8_t *pixel)
{
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}
