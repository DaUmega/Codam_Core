/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 16:57:10 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/06 14:49:16 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	int		i;
	int		j;
	char	*ans;

	i = 0;
	j = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	ans = malloc(sizeof(char) * (l1 + l2 + 1));
	if (!ans)
		return (NULL);
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	while (i < l1 + l2 + 1)
		ans[i++] = s2[j++];
	ans[i] = 0;
	return (ans);
}

// int main()
// {
// 	char *s = ft_strjoin("asdf", "1234");
// 	printf("%s\n", s);
// 	free(s);
// 	return 0;
// }