/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 18:11:09 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/17 00:54:31 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*p1;
	t_list	*p2;

	if (alst == NULL)
		return ;
	p1 = *alst;
	while (p1 != NULL)
	{
		p2 = p1->next;
		ft_lstdelone(&p1, del);
		p1 = p2;
	}
	*alst = NULL;
}
