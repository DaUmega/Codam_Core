/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: paulniezen <paulniezen@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 13:40:27 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/02/01 15:15:33 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define WHITE 4294967295
# define GRAY 10526880
# define BLACK 255
# define RED 4278190335
# define YELLOW 16776960

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

//color.c

int	rgb_to_int(t_rgb color);
int	get_pixel_color(u_int8_t *pixel);

#endif
