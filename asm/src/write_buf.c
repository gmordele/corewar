/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 01:58:40 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/16 02:18:45 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "asm.h"


void		write_buf(int fd, t_data *data)
{
	t_statement_lst	*p;
	long			header_size;

	header_size = sizeof(t_header);
	if (write(fd, &(data->header), header_size) < header_size)
		err_exit_strerror("write()", data);
	p = data->statement_lst;
	while (p != NULL)
	{
		if (p->statement.type == INSTRUCTION)
		{
			if (write(fd, p->statement.instruction.write_buf,
					p->statement.instruction.size) 
				< p->statement.instruction.size)
				err_exit_strerror("write()", data);
		}
		p = p->next;
	}
}
