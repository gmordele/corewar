/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:35:22 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/12 23:20:39 by gmordele         ###   ########.fr       */
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

void			free_token(t_token *token)
{
	if (token->str_val != NULL)
		free(token->str_val);
	free(token);
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

t_token			*get_next_token(int fd, t_data *data)
{
	static int	i = 0;
	static int	row = 1;
	static char	*str = NULL;
	t_token		*token;
	int			ret_gnl;

	data->fd = fd;
	if (str == NULL)
		if ((ret_gnl = get_next_line(data->fd, &str)) <= 0)
			return (end_gnl(ret_gnl, i, row, data));
	pass_space_com(&i, str);
	token = get_token(&str, &i, &row, data);
	if (token == NULL)
	{
		ft_strdel(&str);
		ft_dprintf(2, "Lexical error at [%d:%d]\n", row, i + 1);
		err_exit(data);
	}
	return (token);
}
