/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathfinder.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 16:23:40 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/24 16:16:16 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

/*BFS Pathfinding Algo*/

t_path	*set_current(t_path *current, t_path *next, t_map *data)
{
	if (!current)
	{
		current = ft_calloc(1, sizeof(t_path));
		current->px = data->player_x;
		current->py = data->player_y;
		current->next = NULL;
		data->p_count--;
	}
	else
	{
		pathfree(&current);
		current = NULL;
		current = next;
	}
	return (current);
}

t_path	*findnext(t_path **current, t_map *data)
{
	t_path	*tempc;
	t_path	*next;

	tempc = *current;
	next = NULL;
	while (tempc)
	{
		data->map[tempc->py][tempc->px] = '1';
		if (data->map[tempc->py + 1][tempc->px] != '1')
			newnode(&next, tempc->px, tempc->py + 1, data);
		if (data->map[tempc->py - 1][tempc->px] != '1')
			newnode(&next, tempc->px, tempc->py - 1, data);
		if (data->map[tempc->py][tempc->px + 1] != '1')
			newnode(&next, tempc->px + 1, tempc->py, data);
		if (data->map[tempc->py][tempc->px - 1] != '1')
			newnode(&next, tempc->px - 1, tempc->py, data);
		tempc = tempc->next;
	}
	return (next);
}

int	pathfinder(t_map *data)
{
	t_path	*current;
	t_path	*next;
	int		i;

	current = NULL;
	next = NULL;
	i = 0;
	current = set_current(current, next, data);
	while (lstsize(&current) != 0)
	{
		next = findnext(&current, data);
		current = set_current(current, next, data);
		i++;
	}
	if (data->c_count != 0 || data->e_count != 0 || data->p_count != 0)
		ft_error(data);
	return (i);
}
