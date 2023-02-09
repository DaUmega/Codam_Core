/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:27:24 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/15 21:27:24 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(char *s)
{
	int		i;
	int		j;
	char	*nline;

	i = 0;
	j = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (!s[i] || s[i + 1] == 0)
		return (free(s), NULL);
	nline = malloc(sizeof(char) * (ft_strlena(s) - i + 1));
	if (!nline)
		return (free(s), NULL);
	i++;
	while (s[i])
		nline[j++] = s[i++];
	nline[j] = 0;
	free (s);
	return (nline);
}

char	*this_line(char *s)
{
	int		i;
	char	*line;

	i = 0;
	if (!s[i] || !s)
		return (free(s), NULL);
	while (s[i] != '\n' && s[i])
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (free(s), NULL);
	linemake(s, line, 0);
	return (line);
}

char	*ft_strjoina(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ans;

	i = 0;
	j = 0;
	if (!s2 || (ft_strlena(s1) + ft_strlena(s2) == 0))
		return (NULL);
	ans = malloc(sizeof(char) * (ft_strlena(s1) + ft_strlena(s2) + 1));
	if (!ans)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	while (s2[j])
		ans[i++] = s2[j++];
	ans[i] = 0;
	free(s1);
	return (ans);
}

char	*readfile(int fd, char *buf)
{
	char	*temp;
	int		nread;

	nread = 1;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (nread > 0 && !ft_strchra(buf, '\n'))
	{
		nread = read(fd, temp, BUFFER_SIZE);
		if (nread < 0)
			return (free(temp), NULL);
		temp[nread] = 0;
		buf = ft_strjoina(buf, temp);
	}
	free(temp);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*ans;
	static char	*buf;

	if (fd < 0 || !BUFFER_SIZE || read(fd, 0, 0) < 0)
	{
		buf = NULL;
		return (NULL);
	}
	if (!buf)
		buf = NULL;
	buf = readfile(fd, buf);
	if (!buf)
		return (NULL);
	if (buf[0] == 0)
		return (free(buf), NULL);
	ans = this_line(buf);
	buf = next_line(buf);
	return (ans);
}

// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	int i = 1;
// 	char *s = get_next_line(fd);
// 	while(s)
// 	{
// 		printf("Line %d: %s$", i, s);
// 		i++;
// 		free(s);
// 		s = get_next_line(fd);
// 	}
// 	close(fd);
// 	system("leaks a.out");
// }
