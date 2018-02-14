/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_3_list_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:26:15 by edebise           #+#    #+#             */
/*   Updated: 2018/02/13 17:26:19 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm_0.h"

t_champ	*vm_l_new(t_all *all, char *path, int fd, int nb)
{
	t_champ *new;

	new = (t_champ*)vm_malloc(all, sizeof(t_champ));
	new->path = path;
	new->fd = fd;
	new->nb = nb;
	return (new);
}

t_champ	*vm_l_add_bck(t_champ **list, t_champ *new)
{
	t_champ *tmp;

	ft_ptr(NULL, 2, &new->next, &new->prev);
	if ((tmp = *list))
	{
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
	else
		*list = new;
	return (*list);
}

t_champ	*vm_l_add_frt(t_champ **list, t_champ *new)
{
	ft_ptr(NULL, 2, &new->next, &new->prev);
	if (*list)
	{
		(*list)->prev = new;
		new->next = *list;
	}
	*list = new;
	return (*list);
}

t_champ	*vm_l_del_one(t_champ **list, t_champ *target)
{
	if (list && *list && target && *list == target)
	{
		if ((*list = (*list)->next))
			(*list)->prev = NULL;
		ft_free(1, &target);
	}
	else if (list && *list && target && *list != target)
	{
		if (target->prev)
			target->prev->next = target->next;
		if (target->next)
			target->next->prev = target->prev;
		ft_free(1, &target);
	}
	return (*list);
}

void	vm_l_del(t_champ **list)
{
	while (*list)
		vm_l_del_one(list, *list);
}
