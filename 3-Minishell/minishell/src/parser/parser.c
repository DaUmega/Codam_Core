/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:34:57 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 03:34:57 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*parser(t_list *tokens)
{
	t_list	*ast;

	ast = construct_ast(tokens);
	if (!ast)
		return (NULL);
	return (ast);
}
