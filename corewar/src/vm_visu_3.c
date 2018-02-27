/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:59:18 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/27 17:12:36 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "vm_0.h"

static t_process	*get_proc(t_all *all, int nb)
{
	t_process	*proc;

	proc = all->process_list;
	while (proc != NULL && proc->nb != nb)
		proc = proc->next;
	return (proc);
}

static void	visu_clear_win_proc(t_all *all)
{
	int		i;

	wmove(all->win_proc, 0, 0);
	i = 0;
	while (i++ < 30)
		wprintw(all->win_proc, "%50s", " ");
}

void	visu_print_process(t_all *all)
{
	t_process	*proc;
	static int	alive = 1;

	proc = get_proc(all, all->current_proc);
	if (proc != NULL)
	{
		if (!alive)
			visu_clear_win_proc(all);
		print_proc(all, proc);
		alive = 1;
	}
	else if (alive == 1)
	{
		alive = 0;
		visu_clear_win_proc(all);
		wmove(all->win_proc, 0, 0);
		wprintw(all->win_proc, "Process %4d:\nDEAD", all->current_proc);
	}
	wrefresh(all->win_proc);
}

static t_process	*last_process(t_all *all)
{
	t_process	*proc;

	proc = all->process_list;
	while (proc != NULL && proc->next != NULL)
		proc = proc->next;
	return (proc);
}

void	visu_change_proc(t_all *all, int c)
{
	t_process	*proc;

	proc = get_proc(all, all->current_proc);
	if (proc == NULL)
	{
		proc = all->process_list;
		if (proc == NULL)
			return ;
	}
	if (c == KEY_RIGHT)
	{
		if ((proc = proc->prev) == NULL)
			if ((proc = last_process(all)) == NULL)
				return ;
	}
	if (c == KEY_LEFT)
	{
		if ((proc = proc->next) == NULL)
			if ((proc = all->process_list) == NULL)
				return ;
	}
	all->current_proc = proc->nb;
	visu_print_process(all);
	visu_print_arena(all);
}
