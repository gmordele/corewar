/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:23:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/03/01 15:44:14 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ncurses.h>
#include <sys/time.h>
#include <stdarg.h>
#include "vm_0.h"
#include "op.h"

static void	vm_visu_print_border(t_all *all)
{
	int		i;

	i = 0;
	wattron(all->win_arena, COLOR_PAIR(BORDER_COL));
	while (i < 64 * 3 + 3 + 3)
	{
		mvwprintw(all->win_arena, 0, i, " ");
		mvwprintw(all->win_arena, 65, i++, "  ");
	}
	i = 0;
	while (i < 65)
		mvwprintw(all->win_arena, i++, 64 * 3 + 5, "  ");
	i = 0;
	while (i++ < 64)
		mvwprintw(all->win_arena, 0, (i + 1) * 3 - 1, "%02x ", i - 1);
	i = 0;
	while (i++ < 64)
		mvwprintw(all->win_arena, (i - 1) + 1, 0, "%03x ", (i - 1) * 64);
	wattroff(all->win_arena, COLOR_PAIR(BORDER_COL));
}

void		vm_visu_print_players(t_all *all)
{
	int		row;
	int		color;
	int		i;

	use_default_colors();
	row = 25;
	i = 0;
	while (i < all->nb_champ)
	{
		wmove(all->win_info, row, 0);
		wprintw(all->win_info, "Player %d\n", all->champ[i].nb);
		color = i + 2;
		wattron(all->win_info, COLOR_PAIR(color));
		wprintw(all->win_info, "\t%s", all->champ[i].header.prog_name);
		wattroff(all->win_info, COLOR_PAIR(color));
		++i;
		row += 4;
	}
}

static void	vm_make_windows(t_all *all)
{
	int	side_col;
	int	arena_col;
	int	top_row;
	int	marge;

	top_row = 64 + 2;
	side_col = 50;
	arena_col = 64 * 3 + 4 + 4;
	if (LINES < top_row + 3 || COLS < side_col * 2 + arena_col)
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
	if ((all->win_dial = newwin(LINES - top_row - 1, arena_col,
								top_row + 1, side_col + marge)) == NULL)
		vm_exit(all, "newwin() failed\n");
	scrollok(all->win_dial, 1);
}

void		vm_init_visu(t_all *all)
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
	refresh();
}

void		vm_exit_visu(t_all *all)
{
	if (all->win_arena != NULL)
		delwin(all->win_arena);
	if (all->win_info != NULL)
		delwin(all->win_info);
	if (all->win_dial != NULL)
		delwin(all->win_dial);
	endwin();
}
