/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_offsets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:59:34 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/15 12:20:43 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "op.h"
#include "asm.h"

static t_offset	instruction_size(t_instruction instruc)
{
	t_offset	size;
	int			i;

	size = 1;
	size += instruc.op_instruc.encod_byte ? 1 : 0;
	i = 0;
	while (i < 3 && instruc.param[i].value != NULL)
	{
		if (instruc.param[i].type == T_REG)
			++size;
		else if (instruc.param[i].type == T_IND)
			size += 2;
		else
		{
			if (instruc.op_instruc.index)
				size += 2;
			else
				size += 4;
		}
		++i;
	}
	return (size);
}

void			get_offsets(t_data *data)
{
	t_statement_lst	*p;
	t_offset		offset;

	p = data->statement_lst;
	offset = 0;
	while (p != NULL)
	{
		ft_printf("%hd\n", offset);
		p->offset = offset;
		if (p->statement.type == INSTRUCTION)
			offset += instruction_size(p->statement.instruction);
		p = p->next;
	}
}