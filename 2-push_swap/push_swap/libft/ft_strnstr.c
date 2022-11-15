/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/04 21:40:08 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/12 19:14:30 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	n = ft_strlen(needle);
	while (i + n <= len && haystack[i])
	{
		if (haystack[i] == needle[0] && ft_memcmp(haystack + i, needle, n) == 0)
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

// int main () 
// {
//    const char str[50] = "";
//    char *ans;
//    printf("Before = %s\n", str);
//    ans = strnstr(str, "456", -1);
//    printf("After = %s\n", ans);
//    return(0);
// }