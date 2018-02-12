/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ullong_hex_itoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 21:58:12 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/16 18:04:11 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		get_hex_len(unsigned long long n)
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

static void		fill_number_small(char *buff, unsigned long long n,
								int start, int len)
{
	static char	digits[16] = "0123456789abcdef";

	while (len--)
	{
		buff[start--] = digits[n % 16];
		n /= 16;
	}
}

static void		fill_number_big(char *buff, unsigned long long n,
								int start, int len)
{
	static char	digits[16] = "0123456789ABCDEF";

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
	if (cs.precision < 0 && cs.flags & ZERO && !(cs.flags & MINUS))
		while (cs.min_field > bi.len + bi.add)
		{
			buff[bi.start - bi.len++] = '0';
			--pos_add;
		}
	else if (cs.min_field > bi.len + bi.add && !(cs.flags & MINUS))
		while (cs.min_field-- > bi.len + bi.add)
			buff[bi.start - cs.min_field] = ' ';
	else if (cs.flags & MINUS)
		while (++bi.start < cs.min_field)
			buff[bi.start] = ' ';
	if (bi.add)
	{
		buff[pos_add] = cs.conv == 'x' ? 'x' : 'X';
		buff[pos_add - 1] = '0';
	}
}

int				ullong_hex_itoa(char **buff, unsigned long long n,
							t_conv_spec cs)
{
	t_buff_info	bi;

	bi.add = cs.flags & SHARP && n ? 2 : 0;
	bi.len = get_hex_len(n);
	bi.len = bi.len < cs.precision ? cs.precision : bi.len;
	if (!n && !cs.precision)
		bi.len = 0;
	if (bi.len + bi.add > cs.min_field)
		bi.total_size = bi.len + bi.add;
	else
		bi.total_size = cs.min_field;
	*buff = malloc(bi.total_size);
	if (*buff == NULL)
		return (-1);
	bi.start = (cs.flags & MINUS) ? bi.len + bi.add - 1 : bi.total_size - 1;
	if (cs.conv == 'x')
		fill_number_small(*buff, n, bi.start, bi.len);
	else
		fill_number_big(*buff, n, bi.start, bi.len);
	fill_flags(*buff, bi, cs);
	return (bi.total_size);
}
