/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:51:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/27 16:56:32 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <sys/time.h>
#include <ncurses.h>
#include "vm_0.h"

void	visu_print(t_all *all, char *format, ...)
{
	va_list		ap;

	use_default_colors();
	va_start(ap, format);
	vwprintw(all->win_dial, format, ap);
	va_end(ap);
	wrefresh(all->win_dial);
}

static void	visu_unpause(t_all *all)
{
	nodelay(stdscr, 1);
	all->pause = 0;
}

static void	visu_pause(t_all *all)
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

static void	visu_sleep(t_all *all)
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
