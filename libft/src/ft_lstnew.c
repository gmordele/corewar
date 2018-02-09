/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:34:46 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/17 01:14:01 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	if (content != NULL)
	{
		new->content = malloc(content_size);
		if (new->content != NULL)
		{
			ft_memcpy(new->content, content, content_size);
			new->content_size = content_size;
		}
		else
			new->content_size = 0;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	return (new);
}
