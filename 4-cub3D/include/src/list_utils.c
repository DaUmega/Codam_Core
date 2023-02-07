/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 14:42:19 by kali          #+#    #+#                 */
/*   Updated: 2023/02/07 12:48:48 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	p_angle_set(t_data *data, char c)
{
	if (c == 'E')
		data->player.angle = 0;
	else if (c == 'N')
		data->player.angle = M_PI / 2;
	else if (c == 'W')
		data->player.angle = M_PI;
	else
		data->player.angle = M_PI * 3 / 2;
}

static void	nl_remove(char *s)
{
	int	len;

	if (s)
	{
		len = ft_strlen(s) - 1;
		if (s[len] == '\n')
			s[len] = 0;
	}
}

void	linecopy(char *s, t_data *data)
{
	t_list	*temp;

	temp = NULL;
	if (s && (!(ft_strncmp(s, "NO ", 3)) || !(ft_strncmp(s, "SO ", 3))
			|| !(ft_strncmp(s, "WE ", 3)) || !(ft_strncmp(s, "EA ", 3))
			|| !(ft_strncmp(s, "F ", 2)) || !(ft_strncmp(s, "C ", 2))))
	{
		nl_remove(s);
		temp = ft_lstnew(s);
		if (!temp)
			ft_error(data, "lstnew malloc failed.");
	}
	else
		free(s);
	ft_lstadd_back(&data->list, temp);
	if (!data->first)
		data->first = data->list;
}

int	linecheck(char *s)
{
	if (s && (!(ft_strncmp(s, "NO ", 3)) || !(ft_strncmp(s, "SO ", 3))
			|| !(ft_strncmp(s, "WE ", 3)) || !(ft_strncmp(s, "EA ", 3)))
		&& ft_strlen(s) > 4)
		return (1);
	else if (s && s[0] == '\n' && ft_strlen(s) == 1)
		return (1);
	else if (s && (!(ft_strncmp(s, "F ", 2)) || !(ft_strncmp(s, "C ", 2)))
		&& ft_strlen(s) > 3)
		return (1);
	else
		return (0);
}

void	create_list(int fd, t_data *data)
{
	t_list	*temp;
	char	*s;

	data->list = NULL;
	s = inputparse(fd, data);
	if (!s)
		ft_error(data, "Map Settings aren't correct.");
	nl_remove(s);
	mapinputchk(s);
	while (s)
	{
		temp = ft_lstnew(s);
		if (!temp)
			ft_error(data, "lstnew malloc failed.");
		ft_lstadd_back(&data->list, temp);
		s = get_next_line(fd);
		nl_remove(s);
		mapinputchk(s);
	}
}
