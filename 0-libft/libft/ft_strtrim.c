/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 17:51:27 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/17 17:56:31 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	checker(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		run;
	int		end;
	int		i;
	char	*ans;

	i = 0;
	run = 0;
	end = ft_strlen(s1) - 1;
	while (checker(s1[run], set) && s1[run])
		run++;
	if (!s1[run])
	{
		ans = malloc(sizeof(char) * 1);
		ans[0] = 0;
		return (ans);
	}
	while (checker(s1[end], set) && s1[end])
		end--;
	ans = (char *)malloc(sizeof(char) * (end - run + 2));
	if (!ans)
		return (NULL);
	while (run <= end && s1[run])
		ans[i++] = s1[run++];
	ans[i] = 0;
	return (ans);
}

// int main()
// {
// 	char *s = ft_strtrim("   xxx   xxx", " x");
// 	printf("%s\n", s);
// 	free(s);
// 	return 0;
// }