/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 21:22:38 by edebise           #+#    #+#             */
/*   Updated: 2017/11/24 21:23:06 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pf.h"

int		pf_get_color(t_pf *o)
{
	if (ft_strnstr(o->p1 + 1, "eoc}", 4) || ft_strnstr(o->p1 + 1, "EOC}", 4))
		pf_buf_ncat(o, (o->p1[1] > 95 ? "\x1b[37m" : "\x1b[49m"), 0, 5);
	else if (ft_strnstr(o->p1 + 1, "X}", 2) || ft_strnstr(o->p1 + 1, "0}", 2))
		pf_buf_ncat(o, (o->p1[1] > 65 ? "\x1b[2J\x1b[H" : "\x1b[00m"), 0, 8);
	else if (ft_strnstr(o->p1 + 1, "bk}", 3) || ft_strnstr(o->p1 + 1, "BK}", 3))
		pf_buf_ncat(o, (o->p1[1] > 95 ? "\x1b[30m" : "\x1b[40m"), 0, 5);
	else if (ft_strnstr(o->p1 + 1, "r}", 2) || ft_strnstr(o->p1 + 1, "R}", 2))
		pf_buf_ncat(o, (o->p1[1] > 95 ? "\x1b[31m" : "\x1b[41m"), 0, 5);
	else if (ft_strnstr(o->p1 + 1, "g}", 2) || ft_strnstr(o->p1 + 1, "G}", 2))
		pf_buf_ncat(o, (o->p1[1] > 95 ? "\x1b[32m" : "\x1b[42m"), 0, 5);
	else if (ft_strnstr(o->p1 + 1, "y}", 2) || ft_strnstr(o->p1 + 1, "Y}", 2))
		pf_buf_ncat(o, (o->p1[1] > 95 ? "\x1b[33m" : "\x1b[43m"), 0, 5);
	else if (ft_strnstr(o->p1 + 1, "b}", 2) || ft_strnstr(o->p1 + 1, "B}", 2))
		pf_buf_ncat(o, (o->p1[1] > 95 ? "\x1b[34m" : "\x1b[44m"), 0, 5);
	else if (ft_strnstr(o->p1 + 1, "m}", 2) || ft_strnstr(o->p1 + 1, "M}", 2))
		pf_buf_ncat(o, (o->p1[1] > 95 ? "\x1b[35m" : "\x1b[45m"), 0, 5);
	else if (ft_strnstr(o->p1 + 1, "c}", 2) || ft_strnstr(o->p1 + 1, "C}", 2))
		pf_buf_ncat(o, (o->p1[1] > 95 ? "\x1b[36m" : "\x1b[46m"), 0, 5);
	else if (ft_strnstr(o->p1 + 1, "w}", 2) || ft_strnstr(o->p1 + 1, "W}", 2))
		pf_buf_ncat(o, (o->p1[1] > 95 ? "\x1b[39m" : "\x1b[47m"), 0, 5);
	else
		return (0);
	return (1);
}

int		pf_read_format(t_pf *o)
{
	ft_int(0, 6, &o->hl, &o->sharp, &o->space, &o->left, &o->plus, &o->zero);
	ft_int(-1, 2, &o->one, &o->two);
	while (*o->p1)
	{
		if (*o->p1 == '{' && pf_get_color(o))
			o->p1 = ft_strchr(o->p1, '}') + 1;
		else if (*o->p1 == '%' && (o->p2 = o->p1 + 1))
			return (1);
		else
			pf_buf_ncat(o, o->p1++, 0, 1);
	}
	return (0);
}

void	pf_begin(t_pf *o, char *format_dup, int fd)
{
	o->ret = 0;
	if ((o->p1 = format_dup))
	{
		o->fd = fd;
		o->p1 = format_dup;
		o->p2 = NULL;
		o->buf_len = 0;
		while (*o->p1 && pf_read_format(o))
			pf_get_flag(o);
		pf_buf_empty(o, o->fd);
		free(format_dup);
	}
}

int		pf(const char *restrict format, ...)
{
	t_pf	o;

	va_start(o.va, format);
	pf_begin(&o, ft_strdup(format), 1);
	va_end(o.va);
	return (o.ret);
}

char	*ft_spf(const char *restrict format, ...)
{
	t_pf	o;
	char	*format_dup;

	va_start(o.va, format);
	format_dup = ft_strdup(format);
	o.fd = -1;
	o.p1 = format_dup;
	o.p2 = NULL;
	o.buf_len = 0;
	o.ret_s = NULL;
	o.ret = 0;
	while (*o.p1 && pf_read_format(&o))
		pf_get_flag(&o);
	pf_buf_empty(&o, o.fd);
	free(format_dup);
	va_end(o.va);
	return (o.ret_s);
}
