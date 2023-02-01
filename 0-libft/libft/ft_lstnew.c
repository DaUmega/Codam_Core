/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/05 21:16:01 by pdong         #+#    #+#                 */
/*   Updated: 2023/01/29 12:21:51 by pniezen       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ls;

	ls = (t_list *)malloc(sizeof(t_list));
	if (!ls)
		return (NULL);
	ls->content = content;
	ls->next = NULL;
	return (ls);
}
