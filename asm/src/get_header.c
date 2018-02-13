/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 00:54:39 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/13 02:59:25 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "asm.h"

static void	get_name(int fd, t_data *data)
{
	t_token		*token;

	token = get_next_token(fd, data);
	if (token->type != TOK_STRING)
		syntax_error(token, data);
	if (token->str_val != NULL)
		ft_strncpy(data->header.prog_name, token->str_val, PROG_NAME_LENGTH);
	free_token(token);
	token = get_next_token(fd, data);
	if (token->type != TOK_ENDLINE)
		syntax_error(token, data);
	free_token(token);
}

static void	get_comment(int fd, t_data *data)
{
	t_token		*token;

	token = get_next_token(fd, data);
	if (token->type != TOK_STRING)
		syntax_error(token, data);
	if (token->str_val != NULL)
		ft_strncpy(data->header.comment, token->str_val, COMMENT_LENGTH);
	free_token(token);
	token = get_next_token(fd, data);
	if (token->type != TOK_ENDLINE)
		syntax_error(token, data);
	free_token(token);
}

void		get_header(int fd, t_data *data)
{
	t_token		*token;

	data->header.magic = COREWAR_EXEC_MAGIC;
	token = pass_endl_token(fd, data);
	if (token->type == TOK_COMMAND_NAME)
	{
		free_token(token);
		get_name(fd, data);
		token = pass_endl_token(fd, data);
		if (token->type != TOK_COMMAND_COMMENT)
			syntax_error(token, data);
		get_comment(fd, data);
	}
	else if (token->type == TOK_COMMAND_COMMENT)
	{
		free_token(token);
		get_comment(fd, data);
		token = pass_endl_token(fd, data);
		if (token->type != TOK_COMMAND_NAME)
			syntax_error(token, data);
		get_name(fd, data);
	}
	else
		syntax_error(token, data);
	free_token(token);
}
