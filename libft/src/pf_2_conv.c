/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_2_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 00:13:07 by edebise           #+#    #+#             */
/*   Updated: 2017/11/28 00:13:11 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pf.h"

void	pf_c(t_pf *o, char c)
{
	if (o->left)
		pf_buf_ncat(o, 0, c, 1);
	if (--o->one > 0)
		pf_buf_ncat(o, 0, (o->zero && !(o->left) ? '0' : ' '), o->one);
	if (!(o->left))
		pf_buf_ncat(o, 0, c, 1);
}

void	pf_lc(t_pf *o)
{
	pf_init_s(o);
	pf_unichar((wchar_t)va_arg(o->va, wchar_t), o->s_ptr);
	if (!o->s_ptr[1])
		pf_c(o, *o->s_ptr);
	else
	{
		o->s_len = ft_strlen(o->s_ptr);
		if (o->left)
			pf_buf_ncat(o, o->s_ptr, 0, o->s_len);
		if (o->one > o->s_len)
		{
			if (o->zero && !o->left)
				pf_buf_ncat(o, 0, '0', o->one - o->s_len);
			else
				pf_buf_ncat(o, 0, ' ', o->one - o->s_len);
		}
		if (!(o->left))
			pf_buf_ncat(o, o->s_ptr, 0, o->s_len);
	}
}

void	pf_s(t_pf *o, char *s, wchar_t *ws)
{
	int		n[2];

	ft_bzero(n, 8);
	(!s && !ws) ? s = "(null)" : pf_init_s(o);
	o->s_len = ft_strlen(s);
	while (ws && ws[n[0]])
	{
		if (ws[n[0]] < 0x800)
			n[1] += ws[n[0]] < 0x80 ? 1 : 2;
		else
			n[1] += ws[n[0]] < 0x10000 ? 3 : 4;
		if (o->two > -1 && n[1] > o->two)
			break ;
		n[0]++;
		o->s_len = n[1];
	}
	o->s_len = o->two > -1 && o->two < o->s_len ? o->two : o->s_len;
	if (!o->left && o->one > o->s_len)
		pf_buf_ncat(o, 0, (o->zero ? '0' : ' '), o->one - o->s_len);
	if (s)
		pf_buf_ncat(o, s, 0, o->s_len);
	while (n[0]-- > 0)
		pf_buf_ncat(o, pf_unichar(*ws++, o->s_ptr), 0, -1);
	if (o->left && o->one > o->s_len)
		pf_buf_ncat(o, 0, ' ', o->one - o->s_len);
}

void	pf_b(t_pf *o)
{
	int		l;

	pf_init_s(o);
	pf_bdopux_hl(o, 2);
	if (o->space || o->sharp)
	{
		l = ((o->s_len - 1) / 8 + 1) * 8;
		if (o->sharp && (o->hl < 2 || o->hl--))
			l = ft_pow(2, o->hl + 2) * 8;
		(o->one > l ? pf_buf_ncat(o, NULL, ' ', o->one - l) : 0);
		while (l > o->s_len)
		{
			l -= pf_buf_ncat(o, 0, '0', (l - o->s_len < 8 ? l - o->s_len : 8));
			(o->space && !(l % 8) && l ? pf_buf_ncat(o, NULL, ' ', 1) : 0);
		}
		while (l > 0)
		{
			if (o->space && !(l % 8) && l < o->s_len)
				pf_buf_ncat(o, NULL, ' ', 1);
			o->s_ptr += pf_buf_ncat(o, o->s_ptr, 0, l % 8 ? l % 8 : 8);
			l -= l % 8 ? l % 8 : 8;
		}
	}
	else
		pf_bdfopux_add(o);
}

void	pf_bb(t_pf *o, char *ptr)
{
	if (ptr)
	{
		ptr += o->left && o->two > 1 ? o->two - 1 : 0;
		while (o->two && o->two-- >= -1)
		{
			pf_init_s(o);
			pf_utoa((unsigned char)*ptr, 2, o->s_ptr);
			o->left ? ptr-- : ptr++;
			if ((o->s_len = ft_strlen(o->s_ptr)) < 8)
				pf_buf_ncat(o, NULL, '0', 8 - o->s_len);
			pf_buf_ncat(o, o->s_ptr, 0, 8);
			if (o->space && o->two > 0)
				pf_buf_ncat(o, NULL, ' ', 1);
		}
	}
	else
		pf_buf_ncat(o, "null", 0, 4);
}
