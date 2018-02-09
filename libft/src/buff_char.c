/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 21:49:36 by gmordele          #+#    #+#             */
/*   Updated: 2018/01/17 01:04:55 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	simple_char(char **buff, char c)
{
	if ((*buff = malloc(1)) == NULL)
		return (-1);
	(*buff)[0] = c;
	return (1);
}

int			buff_char(char **buff, char c, t_conv_spec cs)
{
	int	i;

	if (cs.min_field <= 1)
		return (simple_char(buff, c));
	if ((*buff = malloc(cs.min_field)) == NULL)
		return (-1);
	i = cs.min_field - 1;
	if (cs.flags & MINUS)
	{
		(*buff)[0] = c;
		while (i != 0)
			(*buff)[i--] = ' ';
	}
	else
	{
		(*buff)[i] = c;
		while (--i >= 0)
			(*buff)[i] = (cs.flags & ZERO) ? '0' : ' ';
	}
	return (cs.min_field);
}
