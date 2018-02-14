/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_statements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 22:28:14 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/14 04:04:35 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"
#include "libft.h"
#include "op.h"

void		add_label(t_token *token, t_data *data)
{
	char			*name;
	t_statement		stat_label;
	t_statement_lst	*new_lst;

	name = NULL;
	if (token->str_val == NULL
		|| (name = ft_strdup(token->str_val)) == NULL)
	{
		free_token(token);
		err_exit_str("error add_label()", data);
	}
	free_token(token);
	stat_label.type = LABEL;
	stat_label.label.name = name;
	if ((new_lst = malloc(sizeof(t_statement_lst))) == NULL)
	{
		ft_strdel(&name);
		err_exit_str("error add_label()", data);
	}
	new_lst->statement = stat_label;
	new_lst->next = NULL;
	statement_lst_add(new_lst, data);
}

t_op		get_op(char *name)
{
	extern t_op	g_op_tab[];
	int			i;

	i = 0;
	while (g_op_tab[i].name != 0 && !ft_strequ(name, g_op_tab[i].name))
		++i;
	return (g_op_tab[i]);
}

static void	invalid_instruction(t_token *token, t_data *data)
{
	ft_dprintf(2, "Invalid instruction at token ");
	print_token(2, token);
	ft_dprintf(2, "\n");
	free_token(token);
	err_exit(data);
}

static int	is_parameter(int type)
{
	return (type == TOK_DIRECT || type == TOK_INDIRECT || type == TOK_REGISTER
		|| type == TOK_INDIRECT_LABEL || type == TOK_DIRECT_LABEL);
}

static char	*param_type_str(t_token *token)
{
	if (token->type == TOK_INDIRECT || token->type == TOK_LABEL)
		return ("indirect");
	if (token->type == TOK_DIRECT || token->type == TOK_DIRECT_LABEL)
		return ("direct");
	if (token->type == TOK_REGISTER)
		return ("register");
	return ("unknown");
}

static t_arg_type	param_type_int(t_token *token)
{
	if (token->type == TOK_INDIRECT || token->type == TOK_LABEL)
		return (T_IND);
	if (token->type == TOK_DIRECT || token->type == TOK_DIRECT_LABEL)
		return (T_DIR);
	else
		return (T_REG);
}

static void	free_parameters(int i, t_instruction *state_instruct)
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

static void	invalid_parameter(t_token *token, int i,
							t_instruction *state_instruct, t_data *data)
{
	free_parameters(i, state_instruct);
	ft_dprintf(2, "Invalid parameter %d type %s for instruction %s\n",
			   i, param_type_str(token), state_instruct->op_instruc.name);
	free_token(token);
	err_exit(data);
}

static int	correct_param(int type, t_arg_type arg_type)
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

static void	get_parameter(t_token *token, t_instruction *stat_instruct, int i,
						t_data *data)
{
	if (!is_parameter(token->type))
	{
		free_parameters(i, stat_instruct);
		syntax_error(token, data);
	}
	if (token->str_val == NULL
		|| ((stat_instruct->param[i].value = ft_strdup(token->str_val)) == NULL))
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
}

static void	get_parameters(t_instruction *stat_instruc, int fd, t_data *data)
{
	t_token		*token;
	int			i;

	token = get_next_token(fd, data);
	i = 0;
	get_parameter(token, stat_instruc, i++, data);
	free_token(token);
	while (i < stat_instruc->op_instruc.n_args)
	{
		token = get_next_token(fd, data);
		if (token->type != TOK_SEPARATOR)
			syntax_error(token, data);
		free_token(token);
		token = get_next_token(fd, data);
		get_parameter(token, stat_instruc, i, data);
		free_token(token);
		++i;
	}
}

void		add_instruction(t_token *token, int fd, t_data *data)
{
	t_statement		stat_instruc;
	t_statement_lst	*new_lst;
	t_op			instruc_op;

	if (token->str_val == NULL)
	{
		free_token(token);
		err_exit_str("error add_label()", data);
	}
	instruc_op = get_op(token->str_val);
	if (instruc_op.name == 0)
		invalid_instruction(token, data);
	free_token(token);
	ft_bzero(&stat_instruc, sizeof(t_statement));
	stat_instruc.instruction.op_instruc = instruc_op;
	stat_instruc.type = INSTRUCTION;
	get_parameters(&(stat_instruc.instruction), fd, data);
	if ((new_lst = malloc(sizeof(t_statement_lst))) == NULL)
	{
		free_parameters(2, &(stat_instruc.instruction));
		err_exit_strerror("malloc{}", data);
	}
	new_lst->statement = stat_instruc;
	new_lst->next = NULL;
	statement_lst_add(new_lst, data);
}

void		get_statements(int fd, t_data *data)
{
	t_token	*token;

	token = pass_endl_token(fd, data);
	while (token->type != TOK_END)
	{
		if (token->type == TOK_LABEL)
		{
			add_label(token, data);
			token = get_next_token(fd, data);
//			print_token(1, token);
			if (token->type == TOK_INSTRUCTION)
				continue ;
		}
		else if (token->type == TOK_INSTRUCTION)
		{
			add_instruction(token, fd, data);
			token = get_next_token(fd, data);			
		}
		else
			syntax_error(token, data);
		if (token->type != TOK_END && token->type != TOK_ENDLINE)
			syntax_error(token, data);
		free_token(token);
		token = pass_endl_token(fd, data);
	}
	free_token(token);
}
