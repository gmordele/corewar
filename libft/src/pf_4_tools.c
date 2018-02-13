/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_4_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 00:13:34 by edebise           #+#    #+#             */
/*   Updated: 2017/11/28 00:13:38 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pf.h"

void	pf_itoa(t_pf *o, long nb, char *sign, char *s)
{
	char	tmp;

	tmp = '0';
	if (!*sign)
	{
		*sign = nb < 0 ? '-' : '+';
		if (nb / 10)
			pf_itoa(o, (nb < 0 ? -(nb / 10) : nb / 10), sign, s);
		if (*sign == '+' && !o->plus)
			*sign = (o->space ? ' ' : 0);
	}
	else if (nb / 10)
		pf_itoa(o, nb / 10, sign, s);
	tmp += nb < 0 ? -(nb % 10) : nb % 10;
	ft_strncat(s, &tmp, 1);
}

void	pf_utoa(unsigned long nb, int base, char *s)
{
	char	tmp;

	if (nb / base)
		pf_utoa(nb / base, base, s);
	tmp = nb % base > 9 ? nb % base + 'W' : nb % base + '0';
	ft_strncat(s, &tmp, 1);
}

void	pf_bdopux_hl(t_pf *o, int base)
{
	if (*o->p2 == 'd' || *o->p2 == 'i')
	{
		if (!o->hl)
			pf_itoa(o, (int)va_arg(o->va, int), o->s_pfx, o->s_ptr);
		else if (o->hl == -1)
			pf_itoa(o, (short)va_arg(o->va, int), o->s_pfx, o->s_ptr);
		else if (o->hl == -2)
			pf_itoa(o, (char)va_arg(o->va, int), o->s_pfx, o->s_ptr);
		else if (o->hl > 0)
			pf_itoa(o, (long)va_arg(o->va, long), o->s_pfx, o->s_ptr);
	}
	else if (!o->hl)
		pf_utoa((unsigned int)va_arg(o->va, unsigned int), base, o->s_ptr);
	else if (o->hl > 0)
		pf_utoa((unsigned long)va_arg(o->va, unsigned long), base, o->s_ptr);
	else if (o->hl == -2)
		pf_utoa((unsigned char)va_arg(o->va, unsigned int), base, o->s_ptr);
	else if (o->hl == -1)
		pf_utoa((unsigned short)va_arg(o->va, unsigned int), base, o->s_ptr);
	if (*o->s_ptr == '0' && !o->two)
		*o->s_ptr = '\0';
	o->s_len = ft_strlen(o->s_ptr);
}

void	pf_bdfopux_add(t_pf *o)
{
	int	len_pfx;
	int	space;
	int	zero;

	len_pfx = ft_strlen(o->s_pfx);
	if (o->two < 0)
	{
		zero = o->zero && !o->left ? o->one - len_pfx - o->s_len : 0;
		space = zero > 0 ? 0 : o->one - len_pfx - o->s_len;
	}
	else
	{
		zero = o->two - o->s_len > 0 ? o->two - o->s_len : 0;
		space = o->one - len_pfx - zero - o->s_len;
	}
	if (!o->left && space > 0)
		pf_buf_ncat(o, NULL, ' ', space);
	pf_buf_ncat(o, o->s_pfx, 0, 5);
	pf_buf_ncat(o, NULL, '0', zero > 0 ? zero : 0);
	pf_buf_ncat(o, o->s_ptr, 0, -1);
	if (o->left && space > 0)
		pf_buf_ncat(o, NULL, ' ', space);
}

char	*pf_unichar(unsigned int wc, char *str)
{
	char			*tmp;
	int				head;
	unsigned int	w;

	if ((w = wc) > 0x7f)
	{
		tmp = str;
		head = 0x80;
		while (w >> 6 || w & (head >> 1))
		{
			tmp++;
			head = 0x80 + (head >> 1);
			w >>= 6;
		}
		tmp[1] = 0;
		while (tmp > str)
		{
			*tmp-- = 0x80 + (wc & 0x3f);
			wc >>= 6;
		}
		*tmp = head + (wc & 0x3f);
	}
	else
		ft_strcpy(str, (char*)&wc);
	return (str);
}
