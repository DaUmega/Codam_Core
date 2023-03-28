/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:05:36 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 04:05:37 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sort_export(char **expo)
{
	int32_t	i;
	int32_t	smallest;
	char	*tmp;

	i = 0;
	while (expo[i])
	{
		if (expo[i + 1])
		{
			smallest = varname_len(expo[i]);
			if (smallest > varname_len(expo[i + 1]))
				smallest = varname_len(expo[i + 1]);
			if (ft_strncmp(expo[i], expo[i + 1], smallest) > 0)
			{
				tmp = expo[i];
				expo[i] = expo[i + 1];
				expo[i + 1] = tmp;
				i = 0;
				continue ;
			}
		}
		i++;
	}
}

void	print_expo(char **expo)
{
	int32_t	i;
	int32_t	j;

	i = 0;
	while (expo[i])
	{
		write(STDOUT_FILENO, "declare -x ", 12);
		j = varname_len(expo[i]);
		write(STDOUT_FILENO, expo[i], j);
		if (j && expo[i][j])
		{
			write(STDOUT_FILENO, "=", 1);
			printf("\"%s\"\n", &expo[i][j + 1]);
		}
		else
			write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
