/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:23:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/26 03:24:21 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ncurses.h>
#include <sys/time.h>
#include "vm_0.h"
#include "op.h"

# define P0_COL		1
# define P1_COL		2
# define P2_COL		3
# define P3_COL		4
# define P4_COL		5
# define P0_COL_PC	6
# define P1_COL_PC	7
# define P2_COL_PC	8
# define P3_COL_PC	9
# define P4_COL_PC	10
# define BORDER_COL	11
# define SELECT_PC	12

void	visu_print_info(t_all *all);
void	visu_change_proc(t_all *all, int c);

void	vm_init_colors(void)
{
	init_color(COLOR_WHITE, 500, 500, 500);
	init_pair(P0_COL, COLOR_WHITE, COLOR_BLACK);
	init_pair(P0_COL_PC, COLOR_BLACK, COLOR_WHITE);
	init_pair(P1_COL, COLOR_GREEN, COLOR_BLACK);
	init_pair(P1_COL_PC, COLOR_BLACK, COLOR_GREEN);
	init_pair(P2_COL, COLOR_BLUE, COLOR_BLACK);
	init_pair(P2_COL_PC, COLOR_BLACK, COLOR_BLUE);
	init_pair(P3_COL, COLOR_RED, COLOR_BLACK);
	init_pair(P3_COL_PC, COLOR_BLACK, COLOR_RED);
	init_pair(P4_COL, COLOR_YELLOW, COLOR_BLACK);
	init_pair(P4_COL_PC, COLOR_BLACK, COLOR_YELLOW);
	init_pair(BORDER_COL, COLOR_BLACK, COLOR_WHITE);
	init_pair(SELECT_PC, COLOR_BLACK, COLOR_MAGENTA);
}

void	visu_unpause(t_all *all)
{
	nodelay(stdscr, 1);
	all->pause = 0;
}

void	visu_change_speed(t_all *all, int c)
{
	if (c == KEY_HOME)
		all->cycles_sec += 1;
	else if (c == KEY_END)
		all->cycles_sec -= 1;
	else if (c == KEY_PPAGE)
		all->cycles_sec += 10;
	else if (c == KEY_NPAGE)
		all->cycles_sec -= 10;
	if (all->cycles_sec <= 0)
		all->cycles_sec = 1;
	if (all->cycles_sec > 500)
		all->cycles_sec = 500;
	all->time_step = 1000000 / all->cycles_sec;
	visu_print_info(all);
}



void	visu_pause(t_all *all)
{
	int		c;

	all->pause = 1;
	all->last_time.tv_sec = 0;
	all->last_time.tv_usec = 0;
	nodelay(stdscr, 0);
	visu_print_info(all);
	while (42)
	{
		c = getch();
		if (c == ' ')
		{
			visu_unpause(all);
			return ;
		}
		else if (c == '\n')
			return ;
		else if (c == 'q')
			vm_exit(all, NULL);
		else if (c == KEY_HOME || c == KEY_END || c == KEY_NPAGE
				|| c == KEY_PPAGE)
			visu_change_speed(all, c);
		else if (c == KEY_LEFT || c == KEY_RIGHT)
			visu_change_proc(all, c);
	}
}

void	visu_sleep(t_all *all)
{
	struct timeval cur_time;
	struct timeval dif_time;

	if (all->last_time.tv_sec != 0 && all->last_time.tv_usec != 0)
	{
		gettimeofday(&(cur_time), NULL);
		timersub(&cur_time, &(all->last_time), &dif_time);
		if (dif_time.tv_sec == 0 && dif_time.tv_usec < (int)(all->time_step))
			usleep(all->time_step - dif_time.tv_usec);
	}
	gettimeofday(&(all->last_time), NULL);
}

void	visu_print_pcs(t_all *all)
{
	t_process	*process;
	int			row;
	int			col;
	int			color;

	process = all->process_list;
	while (process != NULL)
	{
		col = (process->pc % 64) * 3;
		row  = process->pc / 64;
		wmove(all->win_arena, row + 1, col + 3);
		if (process->nb == all->current_proc)
			color = SELECT_PC;
		else
			color = all->color[process->pc] < 0 ? 6 : all->color[process->pc] + 7;
		wattron(all->win_arena, COLOR_PAIR(color));
		wprintw(all->win_arena, "%02hhx", all->arena[process->pc]);
		wattroff(all->win_arena, COLOR_PAIR(color));
		process = process->next;
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
		wmove(all->win_arena, row + 1, col + 3);
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

void	visu_print_info(t_all *all)
{
	use_default_colors();
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

t_process	*get_proc(t_all *all, int nb)
{
	t_process	*proc;

	proc = all->process_list;
	while (proc != NULL && proc->nb != nb)
		proc = proc->next;
	return (proc);
}

void	print_proc(t_all *all, t_process *proc)
{
	int		i;

	wmove(all->win_proc, 0, 0);
	wprintw(all->win_proc, "Process %4d:\npc: %d\n", proc->nb, proc->pc);
	wprintw(all->win_proc, "op: %s\ncarry: %d\n", proc->op, proc->carry);
	wprintw(all->win_proc, "cycle: %d\nnb_live: %d\n", proc->cycle,
			proc->nb_live);
	wprintw(all->win_proc, "step: %d\n\n", proc->step);
	i = 0;
	while (++i <= REG_NUMBER)
		wprintw(all->win_proc, "reg%02x: %08x\n", i, proc->r[i]);
}

void	visu_print_process(t_all *all)
{
	t_process	*proc;
	static int	alive = 1;

	proc = get_proc(all, all->current_proc);
	if (proc != NULL)
	{
		if (!alive)
			wclear(all->win_proc);
		print_proc(all, proc);
		alive = 1;
	}
	else if (alive == 1)
	{
		alive = 0;
		wclear(all->win_proc);
		wmove(all->win_proc, 0, 0);
		wprintw(all->win_proc, "Process %4d:\nDEAD", all->current_proc);
	}
	wrefresh(all->win_proc);
}

t_process	*last_process(t_all *all)
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

void	vm_visu(t_all *all)
{
	int		c;

	refresh();
	visu_print_arena(all);
	visu_print_info(all);
	visu_print_process(all);
 	if (!all->pause) 
 		visu_sleep(all); 
	if (all->pause == 1)
		visu_pause(all);
	else
	{
		while ((c = getch()) != ERR)
		{
			if (c == ' ')
			{
				visu_pause(all);
				return ;
			}
			else if (c == 'q')
				vm_exit(all, NULL);
			else if (c == KEY_LEFT || c == KEY_RIGHT)
				visu_change_proc(all,c);
		}
	}
}

void	vm_visu_print_border(t_all *all)
{
	int		i;

	i = 0;
	wattron(all->win_arena, COLOR_PAIR(BORDER_COL));
	while (i < 64 * 3 + 3 + 1)
	{
		mvwprintw(all->win_arena, 0, i, " ");
		mvwprintw(all->win_arena, 65, i++, " ");
	}
	i = 0;
	while (i < 65)
	{
		mvwprintw(all->win_arena, i, 0, "  ");
		mvwprintw(all->win_arena, i++, 64 * 3 + 2, "  ");
	}
	i = 0;
	while (i++ < 64)
		mvwprintw(all->win_arena, 0, (i - 1) * 3 + 3, "%02d ", i - 1);
	i = 0;
	while (i++ < 64)
		mvwprintw(all->win_arena, (i - 1) + 1, 0, "%02d ", i - 1);
	wattroff(all->win_arena, COLOR_PAIR(BORDER_COL));
}

void	vm_make_windows(t_all *all)
{
	int	side_col;
	int	arena_col;
	int	top_row;
	int	marge;

	top_row = 64 + 2;
	side_col = 50;
	arena_col = 64 * 3 + 4;
	if (LINES < top_row || COLS < side_col * 2 + arena_col) // to update
		vm_exit(all, "Screen is too small\n");
	marge = (COLS - side_col * 2 - arena_col) / 2;
	if ((all->win_proc = newwin(top_row, side_col, 0, marge)) == NULL)
		vm_exit(all, "newwin() failed\n");
	if ((all->win_arena = newwin(top_row, arena_col, 0, marge + side_col))
		== NULL)
		vm_exit(all, "newwin() failed\n");
	if ((all->win_info = newwin(top_row, side_col, 0, marge + side_col
								+ arena_col)) == NULL)
		vm_exit(all, "newwin() failed\n");
	box(all->win_proc, 0, 0);
	box(all->win_arena, 0, 0);
	box(all->win_info, 0, 0);
}

void	vm_init_visu(t_all *all)
{
	initscr();
	start_color();
	vm_init_colors();
	curs_set(0);
	noecho();
	all->cycles_sec = 50;
	all->time_step = 1000000 / all->cycles_sec;
	all->pause = 1;
	all->current_proc = 1;
	keypad(stdscr, 1);
	vm_make_windows(all);
	vm_visu_print_border(all);
}

void	vm_exit_visu(t_all *all)
{
	if (all->win_arena != NULL)
		delwin(all->win_arena);
	if (all->win_info != NULL)
		delwin(all->win_info);
	endwin();
}
