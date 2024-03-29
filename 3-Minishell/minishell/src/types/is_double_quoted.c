/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_double_quoted.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:33:28 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:33:28 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_double_quoted(char *str)
{
	int32_t	i;

	i = 0;
	while (str[i] != '\"' && str[i])
		i++;
	if (str[i])
		i++;
	while (str[i] != '\"' && str[i])
		i++;
	return (str[i] == '\"');
}
