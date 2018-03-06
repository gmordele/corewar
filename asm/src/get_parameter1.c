/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parameter1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 03:20:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/03/06 16:56:32 by gmordele         ###   ########.fr       */
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

t_token	*get_parameter_token(t_instruction *stat_instruc, int fd, int i,
							t_data *data)
{
	t_token	*ret;

	if ((ret = get_next_token_no_exit(fd, data)) == NULL)
	{
		free_parameters(i, stat_instruc);
		err_exit(data);
	}
	return (ret);
}
