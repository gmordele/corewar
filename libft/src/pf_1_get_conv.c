/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_1_get_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 00:12:52 by edebise           #+#    #+#             */
/*   Updated: 2017/11/28 00:12:57 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pf.h"

void	pf_get_conversion(t_pf *o)
{
	if (*o->p2 == 's' && o->hl < 1)
		pf_s(o, (char*)va_arg(o->va, char*), 0);
	else if (*o->p2 == 'S' || *o->p2 == 's')
		pf_s(o, 0, (wchar_t*)va_arg(o->va, wchar_t*));
	else if (*o->p2 == 'c' && o->hl < 1)
		pf_c(o, va_arg(o->va, int));
	else if (*o->p2 == 'C' || *o->p2 == 'c')
		pf_lc(o);
	else if (*o->p2 == 'd' || *o->p2 == 'D' || *o->p2 == 'i')
		pf_d(o);
	else if (*o->p2 == 'f' || *o->p2 == 'F')
		pf_f(o);
	else if (*o->p2 == 'b')
		pf_b(o);
	else if (*o->p2 == 'B')
		pf_bb(o, (char*)va_arg(o->va, char*));
	else if (*o->p2 == 'o' || *o->p2 == 'O')
		pf_o(o);
	else if (*o->p2 == 'u' || *o->p2 == 'U')
		pf_u(o);
	else if (*o->p2 == 'p' || *o->p2 == 'x' || *o->p2 == 'X')
		pf_px(o);
	else if (*o->p2)
		pf_c(o, *o->p2);
	o->p1 = o->p2 + (*o->p2 ? 1 : 0);
}

void	pf_get_hl(t_pf *o)
{
	while (*o->p2 && ft_strchr("lhLhjz", *o->p2))
	{
		if (*o->p2 == 'h')
			(!o->hl || o->hl == -1) ? o->hl-- : 0;
		else if (o->hl >= 0)
			o->hl += (*o->p2 == 'L' ? 2 : 1);
		o->p2++;
	}
	pf_get_conversion(o);
}

void	pf_get_field(t_pf *o)
{
	if (ft_isdigit(*o->p2))
		o->one = ft_atoi_next(&o->p2);
	if (*o->p2 == '*' && o->p2++)
		if ((o->one = (int)va_arg(o->va, int)) < 0 && ++o->left)
			o->one = -(o->one);
	if (*o->p2 == '.' && o->p2++)
	{
		o->two = ft_atoi_next(&o->p2);
		if (*o->p2 == '*' && o->p2++)
			o->two = (int)va_arg(o->va, int);
	}
	pf_get_hl(o);
}

void	pf_get_flag(t_pf *o)
{
	while (*o->p2 && ft_strchr("# -+0", *o->p2))
	{
		o->sharp += (*o->p2 == '#' ? 1 : 0);
		o->space += (*o->p2 == ' ' ? 1 : 0);
		o->left += (*o->p2 == '-' ? 1 : 0);
		o->plus += (*o->p2 == '+' ? 1 : 0);
		o->zero += (*o->p2++ == '0' ? 1 : 0);
	}
	pf_get_field(o);
}
