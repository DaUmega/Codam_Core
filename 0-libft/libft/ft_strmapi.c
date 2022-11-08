/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 22:00:17 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/05 22:12:03 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ans;
	unsigned int	i;

	i = 0;
	ans = ft_strdup(s);
	if (!ans)
		return (NULL);
	while (ans[i])
	{
		ans[i] = (*f)(i, ans[i]);
		i++;
	}
	return (ans);
}
