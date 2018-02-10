/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 02:46:39 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/10 04:02:07 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "op.h"
#include "asm.h"

static t_token		*token_endl(char **str, int *i, int *row, t_data *data)
{
	int		ret_gnl;
	t_token	*ret;

	ret = NULL;
	ft_strdel(str);
	if ((ret_gnl = get_next_line(data->fd, str)) < 0)
		err_exit_str("Can't read source", data);
	else if (ret_gnl == 0)
		ret = new_token(TOK_END, *row, *i + 1, data);
	else
		ret = new_token(TOK_ENDLINE, *row, *i + 1, data);
	*i = 0;
	++(*row);
	return (ret);
}

static t_token		*token_command(char **str, int *i, int *row, t_data *data)
{
	t_token	*ret;

	if (!ft_strncmp(*str + *i, NAME_CMD_STRING,
				ft_strlen(NAME_CMD_STRING)))
	{
		ret = new_token(TOK_COMMAND_NAME, *row, *i + 1, data);
		ret->str_val = ft_strdup(".name");
		*i += ft_strlen(NAME_CMD_STRING);
	}
	else if (!ft_strncmp(*str + *i, COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
	{
		ret = new_token(TOK_COMMAND_COMMENT, *row, *i + 1, data);
		ret->str_val = ft_strdup(".comment");
		*i += ft_strlen(COMMENT_CMD_STRING);
	}
	else
		ret = NULL;
	return (ret);
}

t_token				*get_token(char **str, int *i, int *row, t_data *data)
{
	t_token		*ret;

	ret = NULL;
	if ((*str)[*i] == 0)
		ret = token_endl(str, i, row, data);
	else if ((*str)[*i] == '.')
		ret = token_command(str, i, row, data);
	return (ret);
}
