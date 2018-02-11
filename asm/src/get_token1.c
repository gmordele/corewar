/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:58:18 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/11 03:08:20 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "asm.h"
#include "op.h"

t_token			*token_string(char **str, int *i, int *row, t_data *data)
{
	int		end;
	t_token	*ret;

	end = *i + 1;
	while ((*str)[end] != '\"')
	{
		if ((*str)[end] == '\0')
			return (NULL);
		++end;
	}
	ret = new_token(TOK_STRING, *row, *i + 1, data);
	if ((ret->str_val = ft_strndup(*str + *i + 1, end - *i - 1)) == NULL)
	{
		free(ret);
		return (NULL);
	}
	*i = end + 1;
	return (ret);
}

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
