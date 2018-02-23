/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:23:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/23 05:54:19 by gmordele         ###   ########.fr       */
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

void	visu_print_info(t_all *all);

void	vm_init_colors(void)
{
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
}

void	visu_unpause(t_all *all)
{
	nodelay(stdscr, 1);
	all->pause = 0;
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
		if (c == '\n')
			return ;
		if (c == 27)
			vm_exit(all, NULL);
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
		mvwprintw(all->win_info, 10, 0, "%d.%d", dif_time.tv_sec, dif_time.tv_usec);
		if (dif_time.tv_sec == 0 && dif_time.tv_usec < (int)(all->time_step))
		{
			mvwprintw(all->win_info, 11, 0, "sleep");
			usleep(dif_time.tv_usec);
			all->valid_time_val = 1;
		}
		else
			all->valid_time_val = 0;
	}
	gettimeofday(&(all->last_time), NULL);
	wrefresh(all->win_info);
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
		wmove(all->win_arena, row, col);
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
		wmove(all->win_arena, row, col);
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
	mvwprintw(all->win_info, 2, 0, "Cycle: %d", all->cycle);
	wrefresh(all->win_info);
}

void	vm_visu(t_all *all)
{
	int		c;

	refresh();
	visu_print_arena(all);
	visu_print_info(all);
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
			else if (c == 27)
				vm_exit(all, NULL);
		}
	}
}

void	vm_init_visu(t_all *all)
{
	all->valid_time_val = 1;
	initscr();
	start_color();
	vm_init_colors();
	curs_set(0);
	noecho();
	all->cycles_sec = 50;
	all->time_step = 1000000 / all->cycles_sec;
	all->pause = 1;
	if ((all->win_arena = newwin(64, 64 * 3 - 1, 0, 0)) == NULL)
		vm_exit(all, "newwin() failed\n");
	if ((all->win_info = newwin(64, 50, 0, 64 * 3 + 1)) == NULL)
		vm_exit(all, "newwin() failed\n");
	box(all->win_arena, 0, 0);
	box(all->win_info, 0, 0);
}

void	vm_exit_visu(t_all *all)
{
	if (all->win_arena != NULL)
		delwin(all->win_arena);
	if (all->win_info != NULL)
		delwin(all->win_info);
	endwin();
}
