/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_visu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:23:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/22 15:31:41 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ncurses.h>
#include "vm_0.h"

void	vm_visu(t_all *all)
{
	char	dum[1];
	(void)all;
	printw("test");
	refresh();
	read(0, dum, 1);
}

void	vm_init_visu(t_all *all)
{
	(void)all;
	initscr();
}

void	vm_exit_visu(t_all *all)
{
	(void)all;
	endwin();
}
