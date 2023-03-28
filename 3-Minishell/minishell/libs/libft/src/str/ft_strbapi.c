/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strbapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:10:33 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 04:10:34 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strbapi(char const *s, bool (*f)(int))
{
	size_t	i;
	size_t	len;

	if ((s == 0) || (f == 0))
		return (0);
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (!f(s[i]))
			return (false);
		i++;
	}
	return (true);
}
