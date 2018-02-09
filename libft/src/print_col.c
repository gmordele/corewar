/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 22:40:18 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/22 22:40:35 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_col1(const char **ft)
{
	if (**ft == 'B')
		to_buff(COL_BLA, 5);
	if (**ft == 'R')
		to_buff(COL_RED, 5);
	if (**ft == 'G')
		to_buff(COL_GRE, 5);
	if (**ft == 'Y')
		to_buff(COL_YEL, 5);
	*ft += 4;
	return (5);
}

int		print_col2(const char **ft)
{
	if (**ft == 'B')
		to_buff(COL_BLU, 5);
	if (**ft == 'M')
		to_buff(COL_MAG, 5);
	if (**ft == 'C')
		to_buff(COL_CYA, 5);
	if (**ft == 'W')
		to_buff(COL_WHI, 5);
	*ft += 4;
	return (5);
}

int		print_col3(const char **ft)
{
	if ((*ft)[3] == 'B')
		to_buff(COL_BLA_BG, 5);
	if ((*ft)[3] == 'R')
		to_buff(COL_RED_BG, 5);
	if ((*ft)[3] == 'G')
		to_buff(COL_GRE_BG, 5);
	if ((*ft)[3] == 'Y')
		to_buff(COL_YEL_BG, 5);
	*ft += 7;
	return (5);
}

int		print_col4(const char **ft)
{
	if ((*ft)[3] == 'B')
		to_buff(COL_BLU_BG, 5);
	if ((*ft)[3] == 'M')
		to_buff(COL_MAG_BG, 5);
	if ((*ft)[3] == 'C')
		to_buff(COL_CYA_BG, 5);
	if ((*ft)[3] == 'W')
		to_buff(COL_WHI_BG, 5);
	*ft += 7;
	return (5);
}
