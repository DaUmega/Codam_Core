/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 19:24:19 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/24 20:12:04 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <math.h>

typedef struct the_map
{
	char	**map;
	int		length;
	int		height;
	int		c_count;
	int		e_count;
	int		p_count;
	int		steps;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_path
{
	int				px;
	int				py;
	struct s_path	*next;
}	t_path;

t_map		*g_data;
mlx_image_t	*g_bunnyw;
mlx_image_t	*g_bunnya;
mlx_image_t	*g_bunnys;
mlx_image_t	*g_bunnyd;
mlx_image_t	*g_knight;
mlx_image_t	*g_wall;
mlx_image_t	*g_grass;
mlx_image_t	*g_hole;
mlx_t		*g_mlx;

void		ft_error(t_map *data);
void		inputchk(char *s);
void		lstfree(t_list **a);
void		pathfree(t_path **a);
void		datafree(t_map *data);
void		nl_remove(char *s);
t_list		*create_list(int fd);
void		parsemap(t_list *list, t_map *data);
void		mapdata(t_map *data);
void		mapcheck(t_map *data);
int			pathfinder(t_map *data);
t_path		*findnext(t_path **current, t_map *data);
t_path		*set_current(t_path *current, t_path *next, t_map *data);
void		newnode(t_path **lst, int x, int y, t_map *data);
int			lstsize(t_path **a);
int32_t		graphics(void);
void		hook(void *param);
int			bercheck(char *s);
void		showplayer(int i);
void		obscheckws(int i);
void		obscheckad(int i);
void		init_imgs(void);
void		init_imgs2(void);
void		clearoldmap(void);
void		my_keyhook(mlx_key_data_t keydata, void *param);
void		showmap(int a);

#endif