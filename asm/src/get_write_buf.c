/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_write_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 12:30:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/15 18:19:34 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <stdio.h>

static char				get_encod_byte(t_instruction instruct)
{
	int		i;
	char	bits;
	char	encod_byte;

	encod_byte = 0;
	i = 0;
	while (i < 3 && instruct.param[i].value != NULL)
	{
		if (instruct.param[i].type & T_DIR)
			bits = 2;
		else if (instruct.param[i].type & T_IND)
			bits = 3;
		else
			bits = 1;
		encod_byte |= bits << (6 - i * 2);
		++i;
	}
	return (encod_byte);
}

static unsigned char	reg_value(char *value)
{
	if (value == NULL)
		return (0);
	if (*value == 'r')
		++value;
	return (ft_atoi(value));
}

static void				write_param(int i, t_instruction instruction, t_data *data)
{
	int		j;

	j = 0;
	while (j < 3 && instruction.param[j].value != NULL)
	{
		if (instruction.param[j].type == T_REG)
			instruction.write_buf[i++] = reg_value(instruction.param[j].value);
		else if (instruction.param[j].type & T_LAB)
			write_buf_label(&i, j, instruction, data);
		else
			write_buf_dir_indir(&i, j, instruction);
		++j;
	}
}

void					get_write_buf(t_data *data)
{
	t_statement_lst	*p;
	int				i;

	p = data->statement_lst;
	while (p != NULL)
	{
		if (p->statement.type == INSTRUCTION)
		{
			if ((p->statement.instruction.write_buf =
				malloc(p->statement.instruction.size)) == NULL)
					err_exit_strerror("malloc()", data);
			p->statement.instruction.write_buf[0] =
				p->statement.instruction.op_instruc->opcode;
			i = 1;
			if (p->statement.instruction.op_instruc->encod_byte)
				p->statement.instruction.write_buf[i++] =
					get_encod_byte(p->statement.instruction);
			write_param(i, p->statement.instruction, data);
		}
		p = p->next;
	}
}
