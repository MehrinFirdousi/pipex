/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 22:30:28 by mfirdous          #+#    #+#             */
/*   Updated: 2022/07/16 14:35:41 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*curr_node;
	t_list	*prev_node;

	curr_node = lst;
	prev_node = lst;
	while (curr_node)
	{
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	return (prev_node);
}
