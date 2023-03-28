/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_joinmatrix.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 13:13:22 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 13:13:23 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinmatrix(const char **matrix, size_t count)
{
	char	*result;
	size_t	total_len;
	size_t	i;

	if (matrix == NULL)
		return ("(null)\n");
	if (count == 0)
		return ("count == 0\n");
	total_len = count - 1;
	total_len += ft_matrixlen((void *)matrix);
	result = ft_calloc(total_len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result = ft_strjoin(result, matrix[i]);
		if (i != 0 || i != count - 1)
			result = ft_strjoin(result, " ");
		i++;
	}
	return (result);
}
