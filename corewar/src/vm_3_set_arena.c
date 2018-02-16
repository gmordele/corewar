/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_3_set_arena.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 16:37:05 by edebise           #+#    #+#             */
/*   Updated: 2018/02/16 16:37:12 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

void	vm_print_arena(t_all *all)
{
	int x;
	int y;

	pf("{X}{W}{bk}   ");
	x = -1;
	while (++x < 64)
		pf(x < 63 ? " %02d" : " %02d   \n", x);
	y = 0;
	while (y < 64)
	{
		pf("{W}{bk}%02d {0}", y);
		x = 0;
		while (x < 64)
		{
			pf(all->color[y * 64 + x] >= 0 ? all->champ[(int)all->color[y * 64 + x]].color : "{0}");
			pf(" %02hhx", all->arena[y * 64 + x]);
			x++;
		}
		pf(" {W}  {0}\n");
		y++;
	}
	pf("{W}%198s{0}\n", "");
}

void	vm_set_arena(t_all *all)
{
	int	delta;
	int	n;

	delta = MEM_SIZE  / all->nb_champ;
	pf("Delta {y}%d\n{0}", delta);
	n = all->nb_champ;
	ft_memset(all->color, -1, MEM_SIZE);
	while (n-- > 0)
	{
		ft_memcpy(all->arena + (delta * n), all->champ[n].prog, all->champ[n].prog_size);
		ft_memset(all->color + (delta * n), n, all->champ[n].prog_size);
	}
	vm_print_arena(all);
}
