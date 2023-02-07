/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cubed.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 10:42:10 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/02/07 09:03:09 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "settings.h"
# include "color.h"
# include <math.h>

typedef struct s_rc{
	float	s_x;
	float	s_y;
	float	e_x;
	float	e_y;
	float	s2_x;
	float	s2_y;
	float	e2_x;
	float	e2_y;
	float	s3_x;
	float	s3_y;
	float	e3_x;
	float	e3_y;
}	t_rc;

typedef struct s_images{
	mlx_image_t	*floor;
	mlx_image_t	*ceiling;
	mlx_image_t	*walls;
	mlx_image_t	*mini_map;
	mlx_image_t	*rays;
}	t_images;

typedef struct s_player{
	double	x;
	double	y;
	double	angle;
	double	speed;
	double	rot_speed;
}	t_player;

typedef struct s_cubed
{
	mlx_texture_t	*n_texture;
	mlx_texture_t	*s_texture;
	mlx_texture_t	*w_texture;
	mlx_texture_t	*e_texture;
	t_rgb			f_color;
	t_rgb			c_color;
	char			**map;
	int				length;
	int				height;
	int				p_count;
	float			num_rays;
	t_player		player;
	t_images		images;
	mlx_t			*mlx;
	t_list			*list;
	t_list			*first;
}	t_data;

//draw.c

void	bresenham(t_data *data, mlx_image_t *img, t_rc coor, bool mini_map);

//playermath.c

void	update_w(t_data *data);
void	update_s(t_data *data);
void	update_a(t_data *data);
void	update_d(t_data *data);

//raymath.c

double	ray_final_x(t_data *data, double angle);
double	ray_final_y(t_data *data, double angle);

//minimap.c

void	draw_mini_map(t_data *data, char **map, float scale);
void	cast_ray(t_data *data);

//minimap_utils.c

float	get_scale(t_data *data);
void	init_minimap(t_data *data);

//init_game.c

void	fill_image(mlx_image_t *img, t_rgb rgb_color);
void	start(t_data *data);

//walls.c

void	build_wall(t_data *data);
double	square(double a);

//parsemap.c
void	mapinputchk(char *s);

//inputparse.c

char	*inputparse(int fd, t_data *data);
t_list	*rulesdata(t_list *list, t_data *data);

//list_utils.c

void	p_angle_set(t_data *data, char c);
void	create_list(int fd, t_data *data);
void	linecopy(char *s, t_data *data);
int		linecheck(char *s);

//free_ft.c

void	ft_error(t_data *data, char *s);
void	free_split(char **s);
void	lstfree(t_list **a);
void	datafree(t_data *data);

//parse_map.c

void	map_parse(t_data *data, int fd);

//key_hook.c

void	key_hooks(void *param);
void	resize_screen(int32_t width, int32_t height, void *param);
bool	wallcheck(t_data *data, double dx, double dy);

//utils.c

void	*alloc_check(void *ptr);
void	exit_on_error(int err_num, char *msg);
void	exit_program(void *param);

#endif