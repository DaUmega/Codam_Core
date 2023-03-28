/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_matrixclear.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:11:10 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 04:11:10 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_matrixfree(char ***string)
{
	size_t	i;

	i = 0;
	if (!*string)
		return ;
	while ((*string)[i])
	{
		free((*string)[i]);
		i++;
	}
	free(*string);
	*string = NULL;
}
