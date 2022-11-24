/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_ft.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 20:08:44 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/24 18:21:38 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(t_map *data)
{
	ft_printf("Error\n");
	if (data)
		datafree(data);
	exit(EXIT_FAILURE);
}

void	lstfree(t_list **a)
{
	t_list	*temp;

	while (*a)
	{
		temp = *a;
		*a = (*a)->next;
		free(temp->content);
		free(temp);
	}
}

void	pathfree(t_path **a)
{
	t_path	*temp;

	while (*a)
	{
		temp = *a;
		*a = (*a)->next;
		free(temp);
	}
}

void	datafree(t_map *data)
{
	int	i;

	i = 0;
	while (data->map[i])
		free(data->map[i++]);
	if (data->map)
		free(data->map);
	if (data)
		free(data);
}

// void	debug(t_map *data)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("MAP:\n");
// 	while (data->map[i])
// 		ft_printf("%s\n", data->map[i++]);
// 	ft_printf("Length(x): %d, Height(y): %d\n", data->length, data->height);
// 	ft_printf("Ccount: %d, Ecount: %d, Pcount %d\n",
// 		data->c_count, data->e_count, data->p_count);
// 	ft_printf("Player_X: %d, Player_Y: %d\n", data->player_x, data->player_y);
// 	ft_printf("Steps: %d\n", data->steps);
// }
