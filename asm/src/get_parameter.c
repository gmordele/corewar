/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parameter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:42:24 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/15 14:19:15 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "libft.h"
#include "op.h"

static t_arg_type	param_type_int(t_token *token)
{
	if (token->type == TOK_INDIRECT)
		return (T_IND);
	if (token->type == TOK_LABEL)
		return (T_IND | T_LAB);
	if (token->type == TOK_DIRECT)
		return (T_DIR);
	if (token->type == TOK_DIRECT_LABEL)
		return (T_DIR | T_LAB);
	return (T_REG);
}

void				free_parameters(int i, t_instruction *state_instruct)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (state_instruct->param[j].value != NULL)
			free(state_instruct->param[j].value);
		++j;
	}
}

static void			invalid_parameter(t_token *token, int i,
							t_instruction *state_instruct, t_data *data)
{
	free_parameters(i, state_instruct);
	ft_dprintf(2, "Invalid parameter %d type %s for instruction %s\n",
			   i, param_type_str(token), state_instruct->op_instruc.name);
	free_token(token);
	err_exit(data);
}

static int			correct_param(int type, t_arg_type arg_type)
{
	int		int_type;

	if (type == TOK_INDIRECT || type == TOK_LABEL)
		int_type =  T_IND;
	else if (type == TOK_DIRECT || type == TOK_DIRECT_LABEL)
		int_type = T_DIR;
	else
		int_type = T_REG;
	return (int_type & arg_type);
}

void				get_parameter(t_token *token, t_instruction *stat_instruct,
								int i, t_data *data)
{
	if (!is_parameter(token->type))
	{
		free_parameters(i, stat_instruct);
		syntax_error(token, data);
	}
	if (token->str_val == NULL
		|| ((stat_instruct->param[i].value = ft_strdup(token->str_val))
			== NULL))
	{
		free_parameters(i, stat_instruct);
		free_token(token);
		err_exit(data);
	}
	if (!correct_param(token->type, stat_instruct->op_instruc.args[i]))
	{
		invalid_parameter(token, i, stat_instruct, data);
		err_exit(data);
	}
	stat_instruct->param[i].type = param_type_int(token);
	if ((stat_instruct->param[i].value = ft_strdup(token->str_val)) == NULL)
		err_exit_str("error ft_strdup()", data);
}
