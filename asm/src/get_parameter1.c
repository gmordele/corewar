/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parameter1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 03:20:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/17 02:19:09 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

void	invalid_instruction(t_token *token, t_data *data)
{
	ft_dprintf(2, "Invalid instruction at token ");
	print_token(2, token);
	ft_dprintf(2, "\n");
	free_token(token);
	err_exit(data);
}

int		is_parameter(int type)
{
	return (type == TOK_DIRECT || type == TOK_INDIRECT || type == TOK_REGISTER
		|| type == TOK_INDIRECT_LABEL || type == TOK_DIRECT_LABEL);
}

char	*param_type_str(t_token *token)
{
	if (token->type == TOK_INDIRECT || token->type == TOK_INDIRECT_LABEL)
		return ("indirect");
	if (token->type == TOK_DIRECT || token->type == TOK_DIRECT_LABEL)
		return ("direct");
	if (token->type == TOK_REGISTER)
		return ("register");
	return ("unknown");
}
