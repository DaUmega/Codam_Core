/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pniezen <pniezen@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 09:53:41 by pniezen       #+#    #+#                 */
/*   Updated: 2023/02/07 13:55:34 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <fcntl.h>
#include <sys/errno.h>

int	extcheck(char *s)
{
	int			i;
	int			j;
	const char	ext[5] = {'.', 'c', 'u', 'b', 0};

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

static int	check_read(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0 || read(fd, 0, 0) < 0)
		ft_error(NULL, "Could not open/read file");
	return (fd);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		fd;

	if (argc != 2 || !extcheck(argv[1]))
		ft_error(NULL, "Argument or file extension error.");
	fd = check_read(argv[1]);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit(0);
	map_parse(data, fd);
	start(data);
	exit(0);
}
