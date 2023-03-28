/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:23:46 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 15:45:43 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>

/* Start of program responsible for
 * handling the hightest form of abstractions, namely
 * keeping track of the status of the program
 * issuing messages when something goes wrong
*/

int	g_exitcode;

int	main(int argc, char **argv, char **envp)
{
	t_minishell	sheldon;

	(void)argv;
	if (argc > 1)
		ft_minishell_exit(USAGE, EXIT_FAILURE);
	if (dup_envp(&sheldon, envp))
	{
		perror("Environment parsing: ");
		exit(EXIT_FAILURE);
	}
	if (!isatty(STDIN_FILENO))
		perror("tty: ");
	g_exitcode = 0;
	while (1)
		minishell(&sheldon);
}
