/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 19:24:16 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/12 20:27:47 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first;
	t_list	*new;

	if (lst == NULL || (first = f(lst)) == NULL)
		return (NULL);
	lst = lst->next;
	new = first;
	while (lst != NULL)
	{
		new->next = f(lst);
		if (new->next == NULL)
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (first);
}
