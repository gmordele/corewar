/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:56:00 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/27 17:12:04 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "vm_0.h"

void	print_proc(t_all *all, t_process *proc)
{
	int		i;

	wmove(all->win_proc, 0, 0);
	wprintw(all->win_proc, "Process %4d:\npc: %d (y %d, x %d)\n", proc->nb, proc->pc, proc->pc / 64, proc->pc % 64);
	wprintw(all->win_proc, "op: %s\ncarry: %d\n", proc->op, proc->carry);
	wprintw(all->win_proc, "cycle: %d\nnb_live: %d\n", proc->cycle,
			proc->nb_live);
	wprintw(all->win_proc, "step: %d\n\n", proc->step);
	i = 0;
	while (++i <= REG_NUMBER)
		wprintw(all->win_proc, "reg%02x: %08x\n", i, proc->r[i]);
}

void	visu_print_info(t_all *all)
{
	static int	begin = 1;

	use_default_colors();
	if (begin)
	{
		begin = 0;
		vm_visu_print_players(all);
	}
	if (all->pause)
		mvwprintw(all->win_info, 0, 0, "PAUSE   ");
	else
		mvwprintw(all->win_info, 0, 0, "RUNNING");
	mvwprintw(all->win_info, 2, 0, "Cycle: %d\n", all->cycle, all->cycles_sec);
	wprintw(all->win_info, "Cycle to die: % 4d\n", CYCLE_TO_DIE - all->cycle_delta);//all->cycle_to_die);
	wprintw(all->win_info, "Cycles/Seconde: % 4d\n", all->cycles_sec);
	wprintw(all->win_info, "Live number: % 4d\n", all->nb_live);
	wprintw(all->win_info, "Check number: % 4d\n", all->nb_checks);
	wprintw(all->win_info, "Process number: % 4d\n", all->nb_process);
	wrefresh(all->win_info);
}

static void	visu_print_pcs(t_all *all)
{
	t_process	*process;
	int			color;
	int			select_pc;

	select_pc = -1;
	process = all->process_list;
	while (process != NULL)
	{
		wmove(all->win_arena, (process->pc / 64) + 1,
			(process->pc % 64 * 3) + 4);
		if (process->nb == all->current_proc)
			select_pc = process->pc;
		color = all->color[process->pc] < 0 ? 6 : all->color[process->pc] + 7;
		wattron(all->win_arena, COLOR_PAIR(color));
		wprintw(all->win_arena, "%02hhx", all->arena[process->pc]);
		wattroff(all->win_arena, COLOR_PAIR(color));
		process = process->next;
	}
	if (select_pc != -1)
	{
		wmove(all->win_arena, (select_pc / 64) + 1, (select_pc % 64 * 3) + 4);
		wattron(all->win_arena, COLOR_PAIR(SELECT_PC));
		wprintw(all->win_arena, "%02hhx", all->arena[select_pc]);
		wattroff(all->win_arena, COLOR_PAIR(SELECT_PC));
	}
}

void	visu_print_arena(t_all *all)
{
	int		i;
	int		col;
	int		row;
	int		color;

	i = 0;
	col = 0;
	row = 0;
	while (i < MEM_SIZE)
	{
		wmove(all->win_arena, row + 1, col + 4);
		color = all->color[i] < 0 ? 1 : all->color[i] + 2;
		wattron(all->win_arena, COLOR_PAIR(color));
		wprintw(all->win_arena, "%02hhx", all->arena[i]);
		wattroff(all->win_arena, COLOR_PAIR(color));
		col += 3;
		++i;
		if (i % 64 == 0)
		{
			col = 0;
			++row;
		}
	}
	visu_print_pcs(all);
	wrefresh(all->win_arena);
}
