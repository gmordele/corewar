/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_5_process_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:01:52 by edebise           #+#    #+#             */
/*   Updated: 2018/02/16 19:01:54 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm_0.h"

t_process	*vm_new_pro(t_all *all, t_process *father, int pc)
{
	t_process *new;

	new = (t_process*)vm_malloc(all, sizeof(t_process));
	if (father)
	{
		ft_memcpy(new->r, father->r, sizeof(int) * (REG_NUMBER + 1));
		new->carry = father->carry;
	}
	new->pc = pc;
	return (new);
}

t_process	*vm_add_pro_frt(t_process **list, t_process *new)
{
	if (*list)
	{
		(*list)->prev = new;
		new->next = *list;
	}
	*list = new;
	return (*list);
}

/*t_process	*vm_add_pro_bck(t_process **list, t_process *new)
{
	t_process *tmp;

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
}*/

t_process	*vm_del_one_pro(t_process **list, t_process *target)
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

void	vm_del_all_pro(t_process **list)
{
	while (*list)
		vm_del_one_pro(list, *list);
}
