/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 13:15:56 by pniezen       #+#    #+#                 */
/*   Updated: 2023/02/07 12:50:34 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	mapdata(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'E'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'S')
			{
				data->p_count++;
				data->player.x = (float)j;
				data->player.y = (float)i;
				p_angle_set(data, data->map[i][j]);
			}
			j++;
			if (j > data->length)
				data->length = j;
		}
		i++;
	}
	data->height = i;
}

static int	space_expose_check(t_data *data, int i, int j)
{
	if ((data->map[i][j] == '0' || data->map[i][j] == 'N'
	|| data->map[i][j] == 'S' || data->map[i][j] == 'E'
	|| data->map[i][j] == 'W') && ((data->map[i - 1][j] == ' '
	|| data->map[i + 1][j] == ' ' || data->map[i][j - 1] == ' '
	|| data->map[i][j + 1] == ' ') || (data->map[i - 1][j] == 0
	|| data->map[i + 1][j] == 0 || data->map[i][j - 1] == 0
	|| data->map[i][j + 1] == 0)))
		return (1);
	else
		return (0);
}

static void	mapcheck(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->p_count != 1)
		ft_error(data, "More than 1 Player Inputs Found.");
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			while (data->map[i][j] == ' ')
				j++;
			if (i == 0 || i == data->height - 1)
				if (data->map[i][j] != '1')
					ft_error(data, "Top or bottom aren't surrounded by walls.");
			if (space_expose_check(data, i, j))
				ft_error(data, "Sneaky object exposed to space!");
			if (data->map[i][j])
				j++;
		}
		i++;
	}
}

static void	parsemap(t_list *list, t_data *data)
{
	int	i;

	i = 0;
	data->map = ft_calloc((ft_lstsize(list) + 1), sizeof(char *));
	if (!data->map)
		ft_error(0, "Map calloc failed.");
	list = rulesdata(list, data);
	while (list)
	{
		data->map[i] = ft_strdup(list->content);
		if (!data->map[i])
			ft_error(data, "Map strdup failed.");
		i++;
		list = list->next;
	}
	data->map[i] = NULL;
	mapdata(data);
	mapcheck(data);
}

void	map_parse(t_data *data, int fd)
{
	create_list(fd, data);
	close(fd);
	parsemap(data->list, data);
	lstfree(&data->list);
}
