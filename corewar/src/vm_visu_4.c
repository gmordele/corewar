/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:00:41 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/27 23:59:39 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "vm_0.h"

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
