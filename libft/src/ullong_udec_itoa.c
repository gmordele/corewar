/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ullong_udec_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 19:48:02 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/17 14:48:51 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		get_decimal_len(unsigned long long n)
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

static void		fill_number(char *buff, unsigned long long n,
							int start, int len)
{
	while (len--)
	{
		buff[start--] = n % 10 + '0';
		n /= 10;
	}
}

static void		fill_flags(char *buff, t_buff_info bi, t_conv_spec cs)
{
	if (cs.precision < 0 && cs.flags & ZERO && !(cs.flags & MINUS))
		while (cs.min_field-- > bi.len)
			buff[bi.start - cs.min_field] = '0';
	else if (cs.min_field > bi.len && !(cs.flags & MINUS))
		while (cs.min_field-- > bi.len)
			buff[bi.start - cs.min_field] = ' ';
	else if (cs.flags & MINUS)
		while (++bi.start < cs.min_field)
			buff[bi.start] = ' ';
}

int				ullong_udec_itoa(char **buff, unsigned long long n,
								t_conv_spec cs)
{
	t_buff_info	bi;

	bi.len = get_decimal_len(n);
	bi.len = bi.len < cs.precision ? cs.precision : bi.len;
	if (!n && !cs.precision)
		bi.len = 0;
	if (bi.len > cs.min_field)
		bi.total_size = bi.len;
	else
		bi.total_size = cs.min_field;
	*buff = malloc(bi.total_size);
	if (*buff == NULL)
		return (-1);
	bi.start = (cs.flags & MINUS) ? bi.len - 1 : bi.total_size - 1;
	fill_number(*buff, n, bi.start, bi.len);
	fill_flags(*buff, bi, cs);
	return (bi.total_size);
}
