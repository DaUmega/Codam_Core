/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_redir.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:33:07 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:33:07 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_redir(int c)
{
	return (c == '>' || c == '<');
}
