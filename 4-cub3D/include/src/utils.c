/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kali <kali@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 12:17:49 by pniezen       #+#    #+#                 */
/*   Updated: 2023/02/06 07:25:19 by kali          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdlib.h>
#include <sys/errno.h>

void	*alloc_check(void *ptr)
{
	if (!ptr)
		exit_on_error(1, " Malloc fail.");
	return (ptr);
}

void	exit_on_error(int err_num, char *msg)
{
	ft_printf("Error\n");
	errno = err_num;
	perror(msg);
	exit(EXIT_FAILURE);
}

void	exit_program(void *param)
{
	t_data	*data;

	data = param;
	mlx_close_window(data->mlx);
	exit(EXIT_SUCCESS);
}
