/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:31:50 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:31:51 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int32_t	ft_minishell_exit(t_message code, t_exitcodes exit_code)
{
	ft_putendl_fd((char *)messages_lookup(code), STDERR_FILENO);
	exit(exit_code);
}

const char	*messages_lookup(t_message code)
{
	const char	*message[] = {
	[USAGE] = "Usage: ./minishell",
	[PROMPT] = "ᕕ( ͡° ͜ʖ ͡°)ᕗ > ",
	[ETTY] = "The filedes is not associated with a terminal",
	};

	return (message[code]);
}
