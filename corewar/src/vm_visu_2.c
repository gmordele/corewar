/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:56:00 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/27 21:39:59 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "vm_0.h"

void		print_proc(t_all *all, t_process *proc)
{
	int		i;
	int		row;

	row = 0;
	wmove(all->win_proc, row, MARGE_PROC - 3);
	wprintw(all->win_proc, "PROCESS %4d", proc->nb);
	row += 2;
	wmove(all->win_proc, row++, MARGE_PROC);
	wprintw(all->win_proc, "pc      : %5d\n", proc->pc);
	wmove(all->win_proc, row++, MARGE_PROC);
	wprintw(all->win_proc, "carry   : %5d", proc->carry);
	wmove(all->win_proc, row++, MARGE_PROC);
	wprintw(all->win_proc, "cycle   : %5d", proc->cycle);
	wmove(all->win_proc, row++, MARGE_PROC);
	wprintw(all->win_proc, "nb_live : %5d", proc->nb_live);
	i = 0;
	while (++i <= REG_NUMBER)
	{
		wmove(all->win_proc, ++row, MARGE_PROC);
		wprintw(all->win_proc, "reg%02x: %08x", i, proc->r[i]);
	}
}

static void	print_info(t_all *all)
{
	int		row;

	row = 2;
	wmove(all->win_info, row++, 0);
	wprintw(all->win_info, "Cycle          : %5d", all->cycle, all->cycles_sec);
	wmove(all->win_info, row++, 0);
	wprintw(all->win_info, "Cycle to die   : %5d",
			CYCLE_TO_DIE - all->cycle_delta);
	wmove(all->win_info, row++, 0);
	wprintw(all->win_info, "Cycles/Seconde : % 5d", all->cycles_sec);
	wmove(all->win_info, row++, 0);
	wprintw(all->win_info, "Live number    : % 5d", all->nb_live);
	wmove(all->win_info, row++, 0);
	wprintw(all->win_info, "Check number   : % 5d", all->nb_checks);
	wmove(all->win_info, row++, 0);
	wprintw(all->win_info, "Process number : % 5d", all->nb_process);
}

void		visu_print_info(t_all *all)
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
	print_info(all);
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
			(process->pc % 64 * 3) + 5);
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
		wmove(all->win_arena, (select_pc / 64) + 1, (select_pc % 64 * 3) + 5);
		wattron(all->win_arena, COLOR_PAIR(SELECT_PC));
		wprintw(all->win_arena, "%02hhx", all->arena[select_pc]);
		wattroff(all->win_arena, COLOR_PAIR(SELECT_PC));
	}
}

void		visu_print_arena(t_all *all)
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
		wmove(all->win_arena, row + 1, col + 5);
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
