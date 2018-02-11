/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 02:46:39 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/11 04:59:45 by gmordele         ###   ########.fr       */
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

	ret = NULL;
	if (!ft_strncmp(*str + *i, NAME_CMD_STRING,
				ft_strlen(NAME_CMD_STRING)))
	{
		if ((ret = new_token(TOK_COMMAND_NAME, *row, *i + 1, data)) != NULL)
			if ((ret->str_val = ft_strdup(".name")) != NULL)
				*i += ft_strlen(NAME_CMD_STRING);
	}
	else if (!ft_strncmp(*str + *i, COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
	{
		if ((ret = new_token(TOK_COMMAND_COMMENT, *row, *i + 1, data)) != NULL)
			if ((ret->str_val = ft_strdup(".comment")) != NULL)
				*i += ft_strlen(COMMENT_CMD_STRING);
	}
	if (ret != NULL && ret->str_val == NULL)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}

static t_token		*token_separator(int *i, int *row, t_data *data)
{
	t_token	*ret;

	ret = new_token(TOK_SEPARATOR, *row, *i + 1, data);
	ret->str_val = ft_strdup(",");
	if (ret->str_val == NULL)
	{
		free(ret);
		ret = NULL;
	}
	++(*i);
	return (ret);
}

static t_token		*token_indirect_label(char **str, int *i, int *row, t_data *data)
{
	t_token	*ret;
	int		end;

	end = *i + 1;
	if ((*str)[end] == '\0' || ft_strchr(LABEL_CHARS, (*str)[end]) == NULL)
		return (NULL);
	while ((*str)[end] != '\0'  && ft_strchr(LABEL_CHARS, (*str)[end]) != NULL)
		++end;
	ret = new_token(TOK_INDIRECT_LABEL, *row, *i + 1, data);
	if ((ret->str_val = ft_strndup(*str + *i, end - *i)) == NULL)
	{
		free(ret);
		return (NULL);
	}
	*i = end;
	return (ret);
}

t_token				*get_token(char **str, int *i, int *row, t_data *data)
{
	if ((*str)[*i] == 0)
		return (token_endl(str, i, row, data));
	else if ((*str)[*i] == '.')
		return (token_command(str, i, row, data));
	else if ((*str)[*i] == '\"')
		return (token_string(str, i, row, data));
	else if ((*str)[*i] == ',')
		return (token_separator(i, row, data));
	else if ((*str)[*i] == 'r')
		return (token_register(str, i, row, data));
	else if (ft_isdigit((*str)[*i]) || (*str)[*i] == '-')
		return (token_indirect(str, i, row, data));
	else if (ft_strchr(LABEL_CHARS, (*str)[*i]) != NULL)
		return (token_instr_lab(str, i, row, data));
	else if ((*str)[*i] == LABEL_CHAR)
		return (token_indirect_label(str, i, row, data));
	else if ((*str)[*i] == DIRECT_CHAR)
		return (token_direct(str, i, row, data));
	return (NULL);
}
