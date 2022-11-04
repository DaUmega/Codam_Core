/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:27:30 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/15 21:27:30 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlena(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchra(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i) != (char)c)
	{
		if (!*(s + i))
			return (NULL);
		i++;
	}
	return ((char *)(s + i));
}

void	linemake(char *s, char *line, int i)
{
	while (s[i] != '\n' && s[i])
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = 0;
}
