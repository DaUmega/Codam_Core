/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexical_analyzer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 03:40:27 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 15:07:19 by dritsema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int32_t	quote_check(char *str)
{
	int32_t	valid;

	valid = 1;
	while (*str && valid)
	{
		if (*str == '\'')
		{
			if (is_single_quoted(str))
				str += skip_single_quotes(str);
			else
				valid = 0;
			continue ;
		}
		if (*str == '\"')
		{
			if (is_double_quoted(str))
				str += skip_double_quotes(str);
			else
				valid = 0;
			continue ;
		}
		str++;
	}
	return (valid);
}

int32_t	check_validity(t_list *tokens)
{
	if (!ft_strncmp(tokens->content, "|", 2))
		return (pipe_check(tokens));
	else if (!ft_strncmp(tokens->content, "<", 2))
		return (input_check(tokens));
	else if (!ft_strncmp(tokens->content, ">", 2))
		return (output_check(tokens));
	else if (!ft_strncmp(tokens->content, ">>", 3))
		return (append_check(tokens));
	else if (!ft_strncmp(tokens->content, "<<", 3))
		return (heredoc_check(tokens));
	return (0);
}

void	print_syntax_error(t_list *tokens)
{
	if (!tokens)
		printf("Minishell: syntax error near unexpected token `newline\'\n");
	else
		printf("Minishell: syntax error near unexpected token `%s\'\n",
			tokens->content);
}

int32_t	analyzer(t_list *tokens)
{
	if (!ft_strncmp(tokens->content, "|", 2))
		return (printf("Minishell: syntax error near unexpected token `|\'\n"),
			1);
	while (tokens)
	{
		if (!quote_check(tokens->content))
			return (printf("Minishell: syntax error, unclosed quotes\n"),
				1);
		if (is_tokenchar(tokens->content))
			if (check_validity(tokens))
				return (print_syntax_error(tokens->next), 1);
		tokens = tokens->next;
	}
	return (0);
}
