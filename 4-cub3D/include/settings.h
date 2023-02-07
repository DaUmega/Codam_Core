/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   settings.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 12:08:09 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/02/01 20:57:03 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768
# define TILE_SIZE 32
# define MINI_SCALE 0.2

# define PLAYER_SIZE 4
# define PLAYER_ANGLE 0
# define PLAYER_SPEED 2
# define PLAYER_ROT_SPEED 1.0
# define MAX_DEPTH 20

double	fov(void);
double	half_fov(void);
double	num_rays(void);
double	half_num_rays(void);
double	delta_angle(void);

#endif
