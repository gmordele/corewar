/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_3_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 00:13:21 by edebise           #+#    #+#             */
/*   Updated: 2017/11/28 00:13:25 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pf.h"

void	pf_d(t_pf *o)
{
	pf_init_s(o);
	if (*o->p2 == 'D' && (*o->p2 = 'd'))
		o->hl = 1;
	pf_bdopux_hl(o, 0);
	pf_bdfopux_add(o);
}

void	pf_f(t_pf *o)
{
	long double	ld;

	if (o->hl > 1)
		ld = (long double)va_arg(o->va, long double);
	else if (o->hl == 1 || *o->p2 == 'F')
		ld = (long double)va_arg(o->va, double);
	else
		ld = (long double)va_arg(o->va, double);
	pf_init_s(o);
	if (ld && (ld < 0 || o->plus))
		*o->s_pfx = (ld < 0 ? '-' : '+');
	o->s_ptr = ft_ftoa(ld < 0 ? -ld : ld);
	if (o->two < 0)
		o->two = 6;
	o->s_ptr = ft_round(o->s_ptr, o->two);
	o->s_len = ft_strlen(o->s_ptr);
	o->two = -1;
	pf_bdfopux_add(o);
	free(o->s_ptr);
}

void	pf_o(t_pf *o)
{
	pf_init_s(o);
	if (*o->p2 == 'O')
		o->hl = 1;
	pf_bdopux_hl(o, 8);
	if (o->sharp && *o->s_ptr != '0' && o->s_len >= o->two)
		*o->s_pfx = '0';
	pf_bdfopux_add(o);
}

void	pf_u(t_pf *o)
{
	pf_init_s(o);
	if (*o->p2 == 'U')
		o->hl = 1;
	pf_bdopux_hl(o, 10);
	pf_bdfopux_add(o);
}

void	pf_px(t_pf *o)
{
	pf_init_s(o);
	if (*o->p2 == 'p' && (o->hl = 1))
		o->sharp++;
	pf_bdopux_hl(o, 16);
	if (*o->p2 == 'p' || (o->sharp && *o->s_ptr && *o->s_ptr != '0'))
		ft_strcpy(o->s_pfx, "0x");
	if (*o->p2 == 'X')
		ft_capital(ft_capital(o->s_pfx) + 5);
	pf_bdfopux_add(o);
}
