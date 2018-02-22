/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:23:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/22 17:52:15 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ncurses.h>
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

void	vm_init_colors(void)
{
	init_pair(P0_COL, COLOR_WHITE, COLOR_BLACK);
	init_pair(P0_COL_PC, COLOR_BLACK, COLOR_WHITE);
	init_pair(P1_COL, COLOR_GREEN, COLOR_BLACK);
	init_pair(P1_COL_PC, COLOR_BLACK, COLOR_GREEN);
	init_pair(P2_COL, COLOR_BLUE, COLOR_BLACK);
	init_pair(P2_COL_PC, COLOR_BLACK, COLOR_BLUE);

}

void	print_value(int value, int color)
{
	color = color < 0 ? 1 : color + 2;
	attron(COLOR_PAIR(color));
	printw("%02hhx", value);
	attroff(COLOR_PAIR(color));
}

void	print_pc(int value, int color)
{
	color = color < 0 ? 6 : color + 7;
	attron(COLOR_PAIR(color));
	printw("%02hhx", value);
	attroff(COLOR_PAIR(color));
}

void	print_pcs(t_all *all)
{
	t_process	*process;
	int			row;
	int			col;

	process = all->process_list;
	while (process != NULL)
	{
		col = (process->pc % 64) * 3;
		row  = process->pc / 64;
		move(row, col);
		print_pc(all->arena[process->pc], all->color[process->pc]);
		process = process->next;
	}
}

void	vm_visu(t_all *all)
{
	int		i;
	int		col;
	int		row;
	vm_init_colors();

	i = 0;
	col = 0;
	row = 0;
	while (i < MEM_SIZE)
	{
		move(row, col);
		print_value(all->arena[i], all->color[i]);
		col += 3;
		++i;
		if (i % 64 == 0)
		{
			col = 0;
			++row;
		}
	}
	mvprintw(row, 0, "%d", all->cycle);
	print_pcs(all);
	refresh();
	getch();
}

void	vm_init_visu(t_all *all)
{
	(void)all;
	initscr();
	start_color();
	curs_set(0);
	noecho();
}

void	vm_exit_visu(t_all *all)
{
	(void)all;
	endwin();
}
