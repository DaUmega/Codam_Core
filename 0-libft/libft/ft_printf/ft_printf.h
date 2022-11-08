/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:56:13 by pdong             #+#    #+#             */
/*   Updated: 2022/10/29 11:12:27 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

size_t	ft_strlen(const char *s);
int		ft_printf(const char *s, ...);
int		ft_p(va_list arg);
int		ft_putpos(unsigned int nbr, const char *hex);
int		ft_putptr(unsigned long long nbr, const char *hex);
int		ft_putall(int nbr, const char *hex);
int		ft_putchar(int c);
int		ft_putstr(char *s);
int		matcher(va_list arg, const char c);
int		ft_di(va_list arg, const char *s);
int		ft_uxx(va_list arg, const char *s);

#endif