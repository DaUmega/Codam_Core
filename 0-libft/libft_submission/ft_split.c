/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 18:52:32 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/10 19:52:14 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

int	wordlen(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		i++;
		len++;
	}
	return (len);
}

int	mem_str(char **ans, int k, int len)
{
	ans[k] = malloc(sizeof(char) * (len + 1));
	if (!ans[k])
	{
		while (k >= 0)
		{
			free(ans[k]);
			k--;
		}
		return (0);
	}
	return (1);
}

char	**arrmake(char const *s, char c, char **ans, int wcount)
{
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	k = 0;
	while (s[i] == c)
		i++;
	while (s[i] && k < wcount)
	{
		j = 0;
		len = wordlen(s, c, i);
		if (mem_str(ans, k, len) == 0)
			return (NULL);
		while (j < len)
			ans[k][j++] = s[i++];
		ans[k][j] = 0;
		k++;
		while (s[i] == c)
			i++;
	}
	ans[k] = NULL;
	return (ans);
}

int	wcounter(char const *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			wcount++;
		while (s[i] != c && s[i])
			i++;
	}
	return (wcount);
}

char	**ft_split(char const *s, char c)
{
	int		wcount;
	int		i;
	char	**ans;

	if (!s || !*s)
	{
		ans = malloc(sizeof(char *) * 1);
		if (!ans)
			return (NULL);
		ans[0] = NULL;
		return (ans);
	}
	wcount = wcounter(s, c);
	i = 0;
	ans = malloc(sizeof(char *) * (wcount + 1));
	if (!ans)
		return (NULL);
	ans = arrmake(s, c, ans, wcount);
	return (ans);
}

// int main()
// {
// 	int i = 0;
// 	char **a = ft_split(NULL, 0);
// 	while (i < 0 + 1)
// 	{
// 		printf("%s\n", a[i]);
// 		free(a[i]);
// 		i++;
// 	}
// 	free(a);
// 	// system("leaks a.out");
// }