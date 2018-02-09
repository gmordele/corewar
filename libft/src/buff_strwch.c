/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_strwch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:41:11 by gmordele          #+#    #+#             */
/*   Updated: 2018/01/17 01:13:35 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		get_strwch_len(wchar_t *strwch)
{
	int len;

	len = 0;
	while (*strwch != L'\0')
		len += get_mb_len(*(strwch++));
	return (len);
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

static void		wchar_buff_cpy(char *s, wchar_t *strwch)
{
	int		len;
	int		i;
	char	wcbuff[MB_CUR_MAX];

	while (*strwch != L'\0')
	{
		len = get_mb_len(*strwch);
		wctomb_len(wcbuff, *strwch, len);
		i = 0;
		while (i < len)
			*(s++) = wcbuff[i++];
		strwch++;
	}
}

int				buff_strwch(char **buff, wchar_t *strwch, t_conv_spec cs)
{
	int len;
	int total_size;
	int start;

	if (strwch == NULL)
		return (buff_string(buff, "(null)", cs));
	len = get_strwch_len(strwch);
	total_size = cs.min_field > len ? cs.min_field : len;
	if ((*buff = malloc(total_size)) == NULL)
		return (-1);
	if (cs.flags & MINUS)
	{
		wchar_buff_cpy(*buff, strwch);
		while (len < total_size)
			(*buff)[len++] = ' ';
		return (total_size);
	}
	start = total_size - len;
	wchar_buff_cpy(*buff + start, strwch);
	while (--start >= 0)
		(*buff)[start] = (cs.flags & ZERO) ? '0' : ' ';
	return (total_size);
}
