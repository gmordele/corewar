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

	if ((tmp = *list))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*list = new;
	return (*list);
}

t_champ	*vm_l_add_frt(t_champ **list, t_champ *new)
{
	if (*list)
		new->next = *list;
	*list = new;
	return (*list);
}

t_champ	*vm_l_del_one(t_champ **list, t_champ *target)
{
	t_champ *tmp;

	if (target == *list)
		*list = (*list)->next;
	else
	{
		tmp = *list;
		while (tmp && tmp->next != target)
			tmp = tmp->next;
		if (tmp)
			tmp->next = target->next;
	}
	ft_free(1, &target);
	return (*list);
}

void	vm_l_del(t_champ **list)
{
	while (*list)
		vm_l_del_one(list, *list);
}
