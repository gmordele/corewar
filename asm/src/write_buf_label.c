/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buf_label.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 15:27:46 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/15 17:51:12 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

static int		compare_labels(char *name, char *seek)
{
	int		i;

	if (name == NULL || seek == NULL)
		return (0);
	if (*name == '%')
		++name;
	if (*name == ':')
		++name;
	i = 0;
	while (seek[i] != '\0' && seek[i] != ':')
		++i;
	seek[i] = '\0';
	return (ft_strequ(name, seek));
}	

static t_offset	seek_label(char *name, t_data *data)
{
	t_statement_lst	*p;

	p = data->statement_lst;
	while (p != NULL)
	{
		if (p->statement.type == LABEL)
			if (compare_labels(name, p->statement.label.name))
				return (p->statement.label.offset);
		p = p->next;
	}
	ft_dprintf(2, "No such label %s\n", name);
	err_exit(data);
	return (0);
}

void			write_buf_label(int *i, int j, t_instruction instruction,
							t_data *data)
{
	t_offset	label_offset;
	short		short_value;
	int			int_value;

	label_offset = seek_label(instruction.param[j].value, data);
	if (instruction.param[j].type & T_IND || instruction.op_instruc.index)
	{
		short_value = reverse_endian_short(label_offset - instruction.offset);
		instruction.write_buf[(*i)++] = ((char *)&(short_value))[0];
		instruction.write_buf[(*i)++] = ((char *)&(short_value))[1];
	}
	else
	{
		int_value = reverse_endian_int(label_offset - instruction.offset);
		instruction.write_buf[(*i)++] = ((char *)&(short_value))[0];
		instruction.write_buf[(*i)++] = ((char *)&(short_value))[1];
		instruction.write_buf[(*i)++] = ((char *)&(short_value))[2];
		instruction.write_buf[(*i)++] = ((char *)&(short_value))[3];
	}
}
