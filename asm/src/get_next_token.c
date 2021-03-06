/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:35:22 by gmordele          #+#    #+#             */
/*   Updated: 2018/03/06 16:56:50 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "op.h"
#include "libft.h"
#include "asm.h"

static void		pass_space_com(int *i, char *str)
{
	while (ft_isspace(str[*i]) && str[*i] != '\0')
		++(*i);
	if (str[*i] == COMMENT_CHAR)
	{
		++(*i);
		while (str[*i] != '\0')
			++(*i);
	}
}

t_token			*new_token(int type, int row, int col, t_data *data)
{
	t_token	*ret;

	if ((ret = malloc(sizeof(t_token))) == NULL)
		err_exit_strerror("error malloc()", data);
	ret->type = type;
	ret->row = row;
	ret->col = col;
	ret->str_val = NULL;
	return (ret);
}

static t_token	*end_gnl(int ret_gnl, int i, int row, t_data *data)
{
	t_token		*ret;

	if (ret_gnl < 0)
	{
		ft_dprintf(2, "Can't read source %s\n", data->file_name);
		err_exit(data);
	}
	ret = new_token(TOK_END, row, i + 1, data);
	return (ret);
}

t_token			*get_next_token_no_exit(int fd, t_data *data)
{
	t_token		*token;
	int			ret_gnl;

	data->fd = fd;
	if (data->str == NULL)
		if ((ret_gnl = get_next_line(data->fd, &(data->str))) <= 0)
			return (end_gnl(ret_gnl, data->i, data->row, data));
	pass_space_com(&(data->i), data->str);
	token = get_token(&(data->str), &(data->i), &(data->row), data);
	if (token == NULL)
	{
		ft_strdel(&(data->str));
		ft_dprintf(2, "Lexical error at [%d:%d]\n", data->row, data->i + 1);
		return (NULL);
	}
	return (token);
}

t_token			*get_next_token(int fd, t_data *data)
{
	t_token		*token;
	int			ret_gnl;

	data->fd = fd;
	if (data->str == NULL)
		if ((ret_gnl = get_next_line(data->fd, &(data->str))) <= 0)
			return (end_gnl(ret_gnl, data->i, data->row, data));
	pass_space_com(&(data->i), data->str);
	token = get_token(&(data->str), &(data->i), &(data->row), data);
	if (token == NULL)
	{
		ft_strdel(&(data->str));
		ft_dprintf(2, "Lexical error at [%d:%d]\n", data->row, data->i + 1);
		err_exit(data);
	}
	return (token);
}
