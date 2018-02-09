/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:44:09 by gmordele          #+#    #+#             */
/*   Updated: 2018/01/17 01:05:26 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

static int	null_strlen(char *s)
{
	int l;

	l = 0;
	if (s == NULL)
		return (0);
	while (*s++)
		++l;
	return (l);
}

static void	update_bi(t_buff_info *bi, t_conv_spec cs, char *str)
{
	bi->len = null_strlen(str);
	bi->len = (cs.precision >= 0 &&
			cs.precision < bi->len) ? cs.precision : bi->len;
	bi->total_size = cs.min_field > bi->len ? cs.min_field : bi->len;
}

int			buff_string(char **buff, char *str, t_conv_spec cs)
{
	t_buff_info	bi;

	if (str == NULL)
		return (buff_string(buff, "(null)", cs));
	update_bi(&bi, cs, str);
	if ((*buff = malloc(bi.total_size)) == NULL)
		return (-1);
	if (cs.flags & MINUS)
	{
		bi.start = 0;
		while (bi.start < bi.len)
			(*buff)[bi.start++] = *(str++);
		while (bi.start < bi.total_size)
			(*buff)[bi.start++] = ' ';
		return (bi.total_size);
	}
	bi.start = bi.total_size - bi.len;
	while (bi.start < bi.total_size)
		(*buff)[bi.start++] = *(str++);
	bi.start = bi.total_size - bi.len;
	while (--bi.start >= 0)
		(*buff)[bi.start] = (cs.flags & ZERO) ? '0' : ' ';
	return (bi.total_size);
}
