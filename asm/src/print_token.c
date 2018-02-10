/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 03:30:49 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/10 03:47:09 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "asm.h"

void		print_token(int fd, t_token *token)
{
	ft_dprintf(fd, "[TOKEN][%03d:%03d] " , token->row, token->col);
	if (token->type == TOK_ENDLINE)
		ft_dprintf(fd, "ENDLINE");
	else if (token->type == TOK_END)
		ft_dprintf(fd, "\"END\" (null)");
	else if (token->type == TOK_COMMAND_NAME)
		ft_dprintf(fd, "COMMAND_NAME \"%s\"", token->str_val);
	else if (token->type == TOK_COMMAND_COMMENT)
		ft_dprintf(fd, "COMMAND_COMMENT \"%s\"", token->str_val);
}
