/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:58:18 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/10 21:36:38 by gmordele         ###   ########.fr       */
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
	while (ft_strchr(LABEL_CHARS, (*str)[end]) != NULL && (*str)[end] != '\0')
		++end;
	if ((*str)[end] == ':')
	{
		ret = new_token(TOK_LABEL, *row,  *i + 1, data);
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
