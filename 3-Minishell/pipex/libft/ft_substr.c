/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 16:39:46 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/07 22:14:07 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ans;

	if (!s)
		return (NULL);
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	ans = (char *)malloc(sizeof(char) * (len + 1));
	if (!ans)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		ans[i] = s[start + i];
		i++;
	}
	ans[i] = 0;
	return (ans);
}

// int main()
// {
// 	char *s = ft_substr("tripouille", 100, 1);
// 	printf("%s\n", s);
// 	free(s);
// 	return 0;
// }