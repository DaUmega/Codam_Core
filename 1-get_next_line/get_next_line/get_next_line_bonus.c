/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:27:49 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/15 21:27:49 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	nline = malloc(sizeof(char) * (ft_strlen(s) - i + 1));
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ans;

	i = 0;
	j = 0;
	if (!s2 || (ft_strlen(s1) + ft_strlen(s2) == 0))
		return (NULL);
	ans = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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

char	*readline(int fd, char *buf)
{
	char	*temp;
	int		nread;

	nread = 1;
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (nread > 0 && !ft_strchr(buf, '\n'))
	{
		nread = read(fd, temp, BUFFER_SIZE);
		if (nread < 0)
			return (free(temp), NULL);
		temp[nread] = 0;
		buf = ft_strjoin(buf, temp);
	}
	free(temp);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*ans;
	static char	*buf[4096];

	if (fd < 0 || !BUFFER_SIZE || read(fd, 0, 0) < 0)
	{
		if (fd >= 0 && fd < 4097 && buf[fd])
			buf[fd] = NULL;
		return (NULL);
	}
	if (!buf[fd])
		buf[fd] = NULL;
	buf[fd] = readline(fd, buf[fd]);
	if (!buf[fd])
		return (NULL);
	if (buf[fd][0] == 0)
		return (free(buf[fd]), NULL);
	ans = this_line(buf[fd]);
	buf[fd] = next_line(buf[fd]);
	return (ans);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main(void)
// {
//     char    *output;
//     int     fd;
//     int     fd2;
//     int     oneorother;
//     fd = open("test.txt", O_RDONLY);
//     fd2 = open("test2.txt", O_RDONLY);
//     output = "AA";
//     oneorother = 0;
//     while (output)
//     {
//         if (oneorother % 2 == 0)
//             output = get_next_line(fd2);
//         else
//             output = get_next_line(fd);
//         oneorother++;
//         printf("%s", output);
//         if (output != NULL)
//             free(output);
//     }
// 	system("leaks a.out");
//     return (0);
// }
