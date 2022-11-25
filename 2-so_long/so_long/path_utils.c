/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 16:23:33 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/25 18:06:15 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft/libft.h"

void	newnode(t_path **lst, int x, int y, t_map *data)
{
	t_path	*temp;
	t_path	*node;

	node = ft_calloc(1, sizeof(t_path));
	if (!node)
		ft_error(data);
	node->px = x;
	node->py = y;
	node->next = NULL;
	if (!*lst)
		*lst = node;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
	if (data->map[y][x] == 'C')
		data->c_count--;
	if (data->map[y][x] == 'E')
		data->e_count--;
	data->map[y][x] = '1';
}

int	lstsize(t_path **a)
{
	t_path	*temp;
	int		i;

	if (!a || !*a)
		return (0);
	temp = *a;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

// void	ft_debug(t_path **lst)
// {
// 	t_path	*temp;

// 	if (!lst || !*lst)
// 		return ;
// 	temp = *lst;
// 	while (temp)
// 	{
// 		ft_printf("X %d Y %d, p %p\n", temp->px, temp->py, temp->next);
// 		temp = temp->next;
// 	}
// 	ft_printf("\n");
// }
