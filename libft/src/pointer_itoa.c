/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:05:35 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/16 18:53:30 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		get_hex_len(unsigned long n)
{
	int len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		++len;
		n /= 16;
	}
	return (len);
}

static void		fill_number(char *buff, unsigned long n,
								int start, int len)
{
	static char	digits[16] = "0123456789abcdef";

	while (len--)
	{
		buff[start--] = digits[n % 16];
		n /= 16;
	}
}

static void		fill_flags(char *buff, t_buff_info bi, t_conv_spec cs)
{
	int	pos_add;

	pos_add = bi.start - bi.len;
	if (cs.min_field > bi.len + 2 && !(cs.flags & MINUS))
		while (cs.min_field-- > bi.len + 2)
			buff[bi.start - cs.min_field] = ' ';
	else if (cs.flags & MINUS)
		while (++bi.start < cs.min_field)
			buff[bi.start] = ' ';
	buff[pos_add] = 'x';
	buff[pos_add - 1] = '0';
}

int				pointer_itoa(char **buff, unsigned long n, t_conv_spec cs)
{
	t_buff_info	bi;

	if (!n && !cs.precision)
		bi.len = 0;
	bi.len = get_hex_len(n);
	bi.len = bi.len < cs.precision ? cs.precision : bi.len;
	if (!n && !cs.precision)
		bi.len = 0;
	if (bi.len + 2 > cs.min_field)
		bi.total_size = bi.len + 2;
	else
		bi.total_size = cs.min_field;
	*buff = malloc(bi.total_size);
	if (buff == NULL)
		return (-1);
	bi.start = (cs.flags & MINUS) ? bi.len + 1 : bi.total_size - 1;
	fill_number(*buff, n, bi.start, bi.len);
	fill_flags(*buff, bi, cs);
	return (bi.total_size);
}
