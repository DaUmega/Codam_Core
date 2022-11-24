/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsemap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 20:11:41 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/24 20:47:05 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

void	nl_remove(char *s)
{
	int	len;

	if (s)
	{
		len = ft_strlen(s) - 1;
		if (s[len] == '\n')
			s[len] = 0;
	}
}

t_list	*create_list(int fd)
{
	t_list					*temp;
	t_list					*map;
	char					*s;
	static unsigned long	len = 0;

	s = get_next_line(fd);
	map = NULL;
	if (!s)
		ft_error(0);
	nl_remove(s);
	inputchk(s);
	while (s)
	{
		if (len == 0)
			len = ft_strlen(s);
		temp = ft_lstnew(s);
		ft_lstadd_back(&map, temp);
		if (len != ft_strlen(s))
			ft_error(0);
		s = get_next_line(fd);
		nl_remove(s);
		inputchk(s);
	}
	return (map);
}

void	mapdata(t_map *data)
{
	int	i;
	int	j;

	i = 0;
	data->length = ft_strlen(data->map[0]);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'C')
				data->c_count++;
			if (data->map[i][j] == 'E')
				data->e_count++;
			if (data->map[i][j] == 'P')
			{
				data->p_count++;
				data->player_x = j;
				data->player_y = i;
			}
			j++;
		}
		i++;
	}
	data->height = i;
}

void	mapcheck(t_map *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->e_count != 1 || data->p_count != 1 || data->c_count < 1)
		ft_error(data);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (i == 0 || i == data->height - 1)
				if (data->map[i][j] != '1')
					ft_error(data);
			j++;
		}
		if (data->map[i][0] != '1'
		|| data->map[i][data->length - 1] != '1')
			ft_error(data);
		i++;
	}
}

void	parsemap(t_list *list, t_map *data)
{
	int		i;

	i = 0;
	data->map = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!data->map)
		ft_error(0);
	while (list)
	{
		data->map[i] = ft_strdup(list->content);
		if (!data->map[i])
		{
			datafree(data);
			ft_error(0);
		}
		i++;
		list = list->next;
	}
	data->map[i] = NULL;
	mapdata(data);
	mapcheck(data);
}
