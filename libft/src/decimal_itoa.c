/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_itoa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:22:09 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/16 17:58:13 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		get_decimal_len(int n)
{
	int len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static void		fill_number(char *buff, int n, int start, int len)
{
	if (n < 0)
	{
		buff[start--] = -(n % 10) + '0';
		n /= -10;
		--len;
	}
	while (len--)
	{
		buff[start--] = n % 10 + '0';
		n /= 10;
	}
}

static void		fill_flags(char *buff, int n, t_buff_info bi, t_conv_spec cs)
{
	int	pos_sign;

	pos_sign = bi.start - bi.len;
	if (cs.precision < 0 && cs.flags & ZERO && !(cs.flags & MINUS))
		while (cs.min_field > bi.len + bi.add)
		{
			buff[bi.start - bi.len++] = '0';
			--pos_sign;
		}
	else if (cs.min_field > bi.len + bi.add && !(cs.flags & MINUS))
		while (cs.min_field-- > bi.len + bi.add)
			buff[bi.start - cs.min_field] = ' ';
	else if (cs.flags & MINUS)
		while (++bi.start < cs.min_field)
			buff[bi.start] = ' ';
	if (bi.add)
	{
		if (n < 0)
			buff[pos_sign] = '-';
		else
			buff[pos_sign] = cs.flags & PLUS ? '+' : ' ';
	}
}

int				decimal_itoa(char **buff, int n, t_conv_spec cs)
{
	t_buff_info	bi;

	bi.add = (n < 0 || cs.flags & SPACE || cs.flags & PLUS) ? 1 : 0;
	bi.len = get_decimal_len(n);
	if (!n && !cs.precision)
		bi.len = 0;
	bi.len = bi.len < cs.precision ? cs.precision : bi.len;
	if (bi.len + bi.add > cs.min_field)
		bi.total_size = bi.len + bi.add;
	else
		bi.total_size = cs.min_field;
	*buff = malloc(bi.total_size);
	if (*buff == NULL)
		return (-1);
	bi.start = (cs.flags & MINUS) ? bi.len + bi.add - 1 : bi.total_size - 1;
	fill_number(*buff, n, bi.start, bi.len);
	fill_flags(*buff, n, bi, cs);
	return (bi.total_size);
}
