/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_backnew.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/26 04:10:53 by pdong         #+#    #+#                 */
/*   Updated: 2023/03/26 04:10:53 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/**
 * @brief Takes ’content’, allocates a node for it
 * and adds that node to the end of the list.
 *
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the content to be
 * allocated and added to the list.
 */
t_list	*ft_lstadd_backnew(t_list **lst, void *content)
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	if (!new_node)
		return (NULL);
	ft_lstadd_back(lst, new_node);
	return (new_node);
}
