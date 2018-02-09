/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ullong_octal_itoa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 18:56:32 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/16 18:21:09 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		get_octal_len(unsigned long long n)
{
	int	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		++len;
		n /= 8;
	}
	return (len);
}

static void		fill_number(char *buff, unsigned long long n,
							int start, int len)
{
	while (len--)
	{
		buff[start--] = n % 8 + '0';
		n /= 8;
	}
}

static void		fill_flags(char *buff, t_buff_info bi,
						t_conv_spec cs)
{
	if (cs.precision < 0 && cs.flags & ZERO && !(cs.flags & MINUS))
		while (cs.min_field > bi.len)
			buff[bi.start - bi.len++] = '0';
	else if (cs.min_field > bi.len && !(cs.flags & MINUS))
		while (cs.min_field-- > bi.len)
			buff[bi.start - cs.min_field] = ' ';
	else if (cs.flags & MINUS)
		while (++bi.start < cs.min_field)
			buff[bi.start] = ' ';
}

int				ullong_octal_itoa(char **buff, unsigned long long n,
								t_conv_spec cs)
{
	t_buff_info	bi;

	if (n == 0 && cs.precision)
		cs.flags &= ~SHARP;
	bi.len = get_octal_len(n);
	bi.len = (cs.precision < 1 && cs.flags & SHARP) ? bi.len + 1 : bi.len;
	bi.len = bi.len < cs.precision ? cs.precision : bi.len;
	if (!n && !cs.precision)
		bi.len = (cs.flags & SHARP) ? 1 : 0;
	if (bi.len > cs.min_field)
		bi.total_size = bi.len;
	else
		bi.total_size = cs.min_field;
	*buff = malloc(bi.total_size);
	if (buff == NULL)
		return (-1);
	bi.start = (cs.flags & MINUS) ? bi.len - 1 : bi.total_size - 1;
	fill_number(*buff, n, bi.start, bi.len);
	fill_flags(*buff, bi, cs);
	return (bi.total_size);
}
