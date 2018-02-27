/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 17:00:41 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/27 17:02:02 by gmordele         ###   ########.fr       */
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
