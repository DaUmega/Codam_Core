/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/15 21:27:14 by pdong         #+#    #+#                 */
/*   Updated: 2022/10/15 21:27:14 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_strjoina(char *s1, char *s2);
char	*ft_strchra(const char *s, int c);
char	*get_next_line(int fd);
size_t	ft_strlena(const char *s);
char	*readline(int fd, char *buf);
char	*next_line(char *s);
char	*this_line(char *s);
void	linemake(char *s, char *line, int i);

#endif