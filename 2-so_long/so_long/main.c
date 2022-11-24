/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/15 19:23:36 by pdong         #+#    #+#                 */
/*   Updated: 2022/11/24 20:51:24 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>

// void	leakchk(void)
// {
// 	system("leaks -q so_long");
// }

void	inputchk(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '1' || s[i] == '0' || s[i] == 'P'
			|| s[i] == 'C' || s[i] == 'E')
			i++;
		else
			ft_error(NULL);
	}
}

int	bercheck(char *s)
{
	int			i;
	int			j;
	const char	ext[5] = {'.', 'b', 'e', 'r', 0};

	i = 0;
	j = 0;
	while (s && s[i] && s[i] != '.')
		i++;
	while (s[i] && ext[j])
	{
		if (s[i] != ext[j])
			return (0);
		i++;
		j++;
	}
	if (s[i] == ext[j])
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	t_list	*list;
	t_map	*copy;

	if (ac != 2 || bercheck(av[1]) == 0)
		ft_error(NULL);
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
		ft_error(0);
	list = create_list(fd);
	close(fd);
	g_data = ft_calloc(1, sizeof(t_map));
	parsemap(list, g_data);
	copy = ft_calloc(1, sizeof(t_map));
	parsemap(list, copy);
	lstfree(&list);
	pathfinder(copy);
	graphics();
	datafree(copy);
	exit(EXIT_SUCCESS);
}
