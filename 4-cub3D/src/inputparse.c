/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inputparse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 13:40:49 by pdong         #+#    #+#                 */
/*   Updated: 2023/02/07 12:55:03 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	colorcoder(t_rgb *color, t_list *list)
{
	char	**temp;

	(void)list;
	temp = ft_split(&list->content[2], ',');
	if (!temp)
		ft_error(NULL, "ft_split fail.");
	(*color).r = -1;
	(*color).g = -1;
	(*color).b = -1;
	if (ft_atoi(temp[0]) >= 0 && ft_atoi(temp[0]) <= 255)
		(*color).r = ft_atoi(temp[0]);
	if (ft_atoi(temp[1]) >= 0 && ft_atoi(temp[1]) <= 255)
		(*color).g = ft_atoi(temp[1]);
	if (ft_atoi(temp[2]) >= 0 && ft_atoi(temp[2]) <= 255)
		(*color).b = ft_atoi(temp[2]);
	free_split(temp);
}

static void	colorchecker(t_data *data)
{
	if (data->c_color.r < 0 || data->c_color.g < 0
		|| data->c_color.b < 0)
		ft_error(data, "Colors input errors. (Must be 0-255)");
	if (data->c_color.r > 255 || data->c_color.g > 255
		|| data->c_color.b > 255)
		ft_error(data, "Colors input errors. (Must be 0-255)");
}

t_list	*rulesdata(t_list *list, t_data *data)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (!(ft_strncmp(list->content, "NO ", 3)))
			data->n_texture = alloc_check(mlx_load_png(&list->content[3]));
		else if (!(ft_strncmp(list->content, "SO ", 3)))
			data->s_texture = alloc_check(mlx_load_png(&list->content[3]));
		else if (!(ft_strncmp(list->content, "WE ", 3)))
			data->w_texture = alloc_check(mlx_load_png(&list->content[3]));
		else if (!(ft_strncmp(list->content, "EA ", 3)))
			data->e_texture = alloc_check(mlx_load_png(&list->content[3]));
		else if (!(ft_strncmp(list->content, "F ", 2)))
			colorcoder(&data->f_color, list);
		else if (!(ft_strncmp(list->content, "C ", 2)))
			colorcoder(&data->c_color, list);
		list = list->next;
		i++;
	}
	colorchecker(data);
	return (list);
}

void	mapinputchk(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s && s[i] && s[i] == ' ')
			i++;
		if (s && s[i] != '1')
			ft_error(NULL, "Improper Walls in Map.");
		i = ft_strlen(s) - 1;
		while (s && s[i] && s[i] == ' ')
			i--;
		if (s && s[i] != '1')
			ft_error(NULL, "Improper Walls in Map.");
		i = 0;
		while (s && s[i])
		{
			if (s[i] == '1' || s[i] == '0' || s[i] == ' '
				|| s[i] == 'N' || s[i] == 'E' || s[i] == 'W' || s[i] == 'S')
				i++;
			else
				ft_error(NULL, "Invalid Characters Found.");
		}
	}
}

char	*inputparse(int fd, t_data *data)
{
	char	*s;
	int		i;

	i = 0;
	while (i < 8)
	{
		s = get_next_line(fd);
		if ((s && s[0] == '\n'))
		{
			free(s);
			i++;
		}
		else if (s && linecheck(s)
			&& (!(ft_strncmp(s, "NO ", 3)) || !(ft_strncmp(s, "SO ", 3))
				|| !(ft_strncmp(s, "WE ", 3)) || !(ft_strncmp(s, "EA ", 3))
				|| !(ft_strncmp(s, "F ", 2)) || !(ft_strncmp(s, "C ", 2))))
		{
			linecopy(s, data);
			i++;
		}
		else
			ft_error(data, "Map Settings aren't correct.");
	}
	s = get_next_line(fd);
	return (s);
}
