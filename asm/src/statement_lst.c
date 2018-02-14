/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statement_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 23:00:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/14 02:33:39 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"

void	statement_lst_free(t_data *data)
{
	t_statement_lst	*p1;
	t_statement_lst	*p2;

	p1 = data->statement_lst;
	while (p1 != NULL)
	{
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
}

void	statement_lst_add(t_statement_lst *statement_lst, t_data *data)
{
	t_statement_lst	*p;

	if (data->statement_lst == NULL)
	{
		data->statement_lst = statement_lst;
		return ;
	}
	p = data->statement_lst;
	while (p->next != NULL)
		p = p->next;
	p->next = statement_lst;
}
