/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buf_dir_indir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 17:13:19 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/16 01:47:39 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static int		int_value(char *value)
{
	if (value == NULL)
		return (0);
	if (*value == '%')
		++value;
	return (ft_atoi(value));
}

static short	short_value(char *value)
{
	if (value == NULL)
		return (0);
	if (*value == '%')
		++value;
	return (ft_atoi(value));	
}

void			write_buf_dir_indir(int *i, int j, t_instruction instruction)
{
	int		int_val;
	short	short_val;

	if (instruction.param[j].type & T_IND || instruction.op_instruc->index)
	{
		short_val = short_value(instruction.param[j].value);
		instruction.write_buf[(*i)++] = ((char *)&(short_val))[1];
		instruction.write_buf[(*i)++] = ((char *)&(short_val))[0];		
	}
	else
	{
		int_val = int_value(instruction.param[j].value);
		instruction.write_buf[(*i)++] = ((char *)&(int_val))[3];
		instruction.write_buf[(*i)++] = ((char *)&(int_val))[2];
		instruction.write_buf[(*i)++] = ((char *)&(int_val))[1];
		instruction.write_buf[(*i)++] = ((char *)&(int_val))[0];
	}
}
