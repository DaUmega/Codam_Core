/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pair.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:04:27 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 13:17:34 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pair_clean(t_pair *pair)
{
	if (pair->key)
		free(pair->key);
	if (pair->value)
		free(pair->value);
	if (pair)
		free(pair);
}

char	*pair_to_str(t_pair *pair)
{
	char	*str;
	size_t	length;

	length = ft_strlen(pair->key) + ft_strlen(pair->value) + 2;
	str = ft_calloc(length, sizeof(char));
	if (!str)
	{
		perror("calloc fail");
		exit(EXIT_FAILURE);
	}
	ft_strlcat(str, pair->key, length);
	ft_strlcat(str, "=", length);
	ft_strlcat(str, pair->value, length);
	return (str);
}
