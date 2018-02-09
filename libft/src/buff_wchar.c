/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_wchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 22:01:19 by gmordele          #+#    #+#             */
/*   Updated: 2018/01/17 01:14:20 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int				get_mb_len(wint_t wc)
{
	if (wc < 0x80 || MB_CUR_MAX == 1)
		return (1);
	if (wc < 0x800)
		return (2);
	if (wc < 0x10000)
		return (3);
	return (4);
}

static void		wctomb_len(char *s, wchar_t wc, int len)
{
	int i;

	if (len == 1)
		s[0] = wc;
	else
	{
		i = len - 1;
		while (i > 0)
		{
			s[i--] = 0x80 | (0xFF >> 2 & wc);
			wc >>= 6;
		}
		s[0] = wc | (0xFF << (8 - len));
	}
}

int				buff_wchar(char **buff, wint_t wc, t_conv_spec cs)
{
	int	len;
	int	total_size;
	int	start;

	len = get_mb_len(wc);
	total_size = cs.min_field > len ? cs.min_field : len;
	if ((*buff = malloc(total_size)) == NULL)
		return (-1);
	if (cs.flags & MINUS)
	{
		wctomb_len(*buff, wc, len);
		while (len < cs.min_field)
			(*buff)[len++] = ' ';
		return (total_size);
	}
	start = total_size - len;
	wctomb_len(*buff + start, wc, len);
	while (--start >= 0)
		(*buff)[start] = (cs.flags & ZERO) ? '0' : ' ';
	return (total_size);
}
