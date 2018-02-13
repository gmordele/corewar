/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_endl_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 02:11:05 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/13 02:33:20 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"

t_token		*pass_endl_token(int fd, t_data *data)
{
	t_token	*ret;

	ret = get_next_token(fd, data);
	while (ret->type == TOK_ENDLINE)
	{
		free_token(ret);
		ret = get_next_token(fd, data);
	}
	return (ret);
}
