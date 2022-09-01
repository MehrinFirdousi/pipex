/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:14:36 by mfirdous          #+#    #+#             */
/*   Updated: 2022/07/18 12:26:57 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;
	t_list	*new_node;

	new_list = 0;
	node = lst;
	while (node)
	{
		new_node = ft_lstnew(f(node->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			ft_lstdelone(new_node, del);
			return (0);
		}
		ft_lstadd_back(&new_list, new_node);
		node = node->next;
	}
	return (new_list);
}
