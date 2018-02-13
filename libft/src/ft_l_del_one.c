/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_del_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 21:15:23 by edebise           #+#    #+#             */
/*   Updated: 2018/02/06 21:15:27 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_l_del_one(t_lst **list, t_lst *target)
{
	if (list && *list && target && *list == target)
	{
		if ((*list = (*list)->next))
			(*list)->prev = NULL;
		ft_free(2, &target->str, &target);
	}
	else if (list && *list && target && *list != target)
	{
		if (target->prev)
			target->prev->next = target->next;
		if (target->next)
			target->next->prev = target->prev;
		ft_free(2, &target->str, &target);
	}
	return (*list);
}
