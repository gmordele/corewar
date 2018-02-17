/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_4_set_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proso <proso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:01:47 by proso             #+#    #+#             */
/*   Updated: 2018/02/16 19:36:40 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

void	vm_set_process(t_all *all)
{
	int			pc_delta;
	int			pc;
	int			i;
	t_process	*new;

	pc_delta = MEM_SIZE / all->nb_champ;
	ft_int(0, 2, &pc, &i);
	while (all->nb_champ)
	{
		new = (t_process*)vm_malloc(all, sizeof(t_process));
		new->pc = pc;
		pc += pc_delta;
		new->r[1] = all->champ[i].nb;
		new->num = i++;
		vm_add_pro_frt(&all->process_list, new);
		all->nb_champ--;
	}
}
