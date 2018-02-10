/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:35:22 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/10 21:36:15 by gmordele         ###   ########.fr       */
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



t_token			*get_next_token(int fd, t_data *data)
{
	static 	int 	i = 0;
	static 	int		row = 1;
	static	char	*str = NULL;
	t_token	*token;

	data->fd = fd;
	if (str == NULL)
		if (get_next_line(data->fd, &str) < 0)
			err_exit_str("Can't read source", data);
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

