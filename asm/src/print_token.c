/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 03:30:49 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/10 20:57:46 by gmordele         ###   ########.fr       */
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
	else if (token->type == TOK_STRING)
		ft_dprintf(fd, "STRING \"\"%s\"\"", token->str_val);
	else if (token->type == TOK_SEPARATOR)
		ft_dprintf(fd, "SEPARATOR \"%s\"", token->str_val);
	else if (token->type == TOK_LABEL)
		ft_dprintf(fd, "LABEL \"%s\"", token->str_val);
	else if (token->type == TOK_INSTRUCTION)
		ft_dprintf(fd, "INSTRUCTION \"%s\"", token->str_val);
}
