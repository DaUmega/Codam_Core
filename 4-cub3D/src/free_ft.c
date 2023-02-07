/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_ft.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 09:41:38 by paulniezen    #+#    #+#                 */
/*   Updated: 2023/02/07 09:00:48 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	ft_error(t_data *data, char *s)
{
	ft_printf("Error\n");
	ft_printf("%s\n", s);
	if (data)
		datafree(data);
	exit(EXIT_FAILURE);
}

void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		free(s[i++]);
	free(s);
}

void	lstfree(t_list **a)
{
	t_list	*temp;

	while (*a)
	{
		temp = *a;
		*a = (*a)->next;
		if (temp->content)
			free(temp->content);
		if (temp)
			free(temp);
	}
}

void	datafree(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
			free(data->map[i++]);
		free(data->map);
	}
	if (data->n_texture && data->s_texture
		&& data->w_texture && data->e_texture)
	{
		mlx_delete_texture(data->n_texture);
		mlx_delete_texture(data->s_texture);
		mlx_delete_texture(data->w_texture);
		mlx_delete_texture(data->e_texture);
	}
	if (data)
	{
		if (data->first)
			lstfree(&data->first);
		free(data);
	}
}
