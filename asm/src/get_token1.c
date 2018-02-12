/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:58:18 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/12 03:37:45 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "asm.h"
#include "op.h"

static int		add_line(char **ret, char **str, int begin, int end)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	if (*ret == NULL)
		*ret = ft_strndup(*str + begin, end - begin);
	else
	{
		len = ft_strlen(*ret);
		if ((tmp = malloc(len + 2)) == NULL)
			return (-1);
		tmp[len] = '\n';
		tmp[len + 1] = '\0';
		ft_memcpy(tmp, *ret, len);
		ft_strdel(ret);
		if ((tmp2 = ft_strndup(*str + begin, end - begin)) == NULL)
		{
			ft_strdel(&tmp);
			return (-1);
		}
		*ret = ft_strjoin(tmp, tmp2);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	return (*ret == NULL ? -1 : 0);
}

static char		*get_string(char **str, int *i, int *row, t_data *data)
{
	int		end;
	int		begin;
	int		n_row;
	char	*ret;
	
	ret = NULL;
	begin = *i + 1;
	end = begin;
	n_row = *row;
	while ((*str)[end] != '\"')
	{
		if ((*str)[end] == '\0')
		{
			if (add_line(&ret, str, begin, end) < 0)
			{
				ft_strdel(&ret);
				return (NULL);
			}
			ft_strdel(str);
			if (get_next_line(data->fd, str) <= 0)
			{
				ft_strdel(&ret);
				return (NULL);
			}
			++n_row;
			begin = 0;
			end = 0;
		}
		else
			++end;
	}
	if (add_line(&ret, str, begin, end) < 0)
		ft_strdel(&ret);
	else
	{
		*row = n_row;
		*i = end + 1;
	}
	return (ret);
}

t_token			*token_string(char **str, int *i, int *row, t_data *data)
{
	t_token	*ret;
	char	*str_val;
	int		tmp_i;
	int		tmp_row;

	tmp_i = *i;
	tmp_row = *row;
	if ((str_val = get_string(str, &tmp_i, &tmp_row, data)) == NULL)
		return (NULL);
	ret = new_token(TOK_STRING, *row, *i + 1, data);
	if (ret != NULL)
	{
		*i = tmp_i;
		*row = tmp_row;
		ret->str_val = str_val;
	}
	else
		free(str_val);
	return (ret);
}

/* t_token			*token_string(char **str, int *i, int *row, t_data *data) */
/* { */
/* 	int		end; */
/* 	t_token	*ret; */

/* 	end = *i + 1; */
/* 	while ((*str)[end] != '\"') */
/* 	{ */
/* 		if ((*str)[end] == '\0') */
/* 			return (NULL); */
/* 		++end; */
/* 	} */
/* 	ret = new_token(TOK_STRING, *row, *i + 1, data); */
/* 	if ((ret->str_val = ft_strndup(*str + *i + 1, end - *i - 1)) == NULL) */
/* 	{ */
/* 		free(ret); */
/* 		return (NULL); */
/* 	} */
/* 	*i = end + 1; */
/* 	return (ret); */
/* } */

t_token			*token_instr_lab(char **str, int *i, int *row, t_data *data)
{
	int		end;
	t_token	*ret;

	end = *i + 1;
	while ((*str)[end] != '\0' && ft_strchr(LABEL_CHARS, (*str)[end]) != NULL)
		++end;
	if ((*str)[end] == LABEL_CHAR)
	{
		ret = new_token(TOK_LABEL, *row, *i + 1, data);
		++end;
	}
	else
		ret = new_token(TOK_INSTRUCTION, *row, *i + 1, data);
	if ((ret->str_val = ft_strndup(*str + *i, end - *i)) == NULL)
	{
		free(ret);
		ret = NULL;
	}
	*i = end;
	return (ret);
}

static int		is_indirect(char *str, int i)
{
	while (str[i] != '\0' && ft_isdigit(str[i]))
		++i;
	if (str[i] == '\0')
		return (1);
	if (ft_strchr(LABEL_CHARS, str[i]) != NULL || str[i] == LABEL_CHAR)
		return (0);
	return (1);
}

t_token			*token_indirect(char **str, int *i, int *row, t_data *data)
{
	int		end;
	t_token	*ret;

	if ((*str)[*i] == '-' && !ft_isdigit((*str)[*i + 1]))
		return (NULL);
	if ((*str)[*i] != '-')
		if (!is_indirect(*str, *i))
			return (token_instr_lab(str, i, row, data));
	end = *i + 1;
	if ((*str)[*i] == '-')
		++end;
	while ((*str)[*i] != '\0' && ft_isdigit((*str)[end]))
		++end;
	ret = new_token(TOK_INDIRECT, *row, *i + 1, data);
	if ((ret->str_val = ft_strndup(*str + *i, end - *i)) == NULL)
	{
		free(ret);
		return (NULL);
	}
	*i = end;
	return (ret);
}
