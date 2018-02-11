/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 03:18:33 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/11 04:59:25 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "asm.h"
#include "op.h"

static int		is_register(char *str, int i)
{
	++i;
	if (!ft_isdigit(str[i]))
		return (0);
	++i;
	if (str[i] == '\0' || ft_strchr(LABEL_CHARS, str[i]) == NULL)
		return (1);
	if (ft_isdigit(str[i]))
	{
		i++;
		if (str[i] == '\0' || ft_strchr(LABEL_CHARS, str[i]) == NULL)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

t_token			*token_register(char **str, int *i, int *row, t_data *data)
{
	t_token	*ret;
	int		end;

	if (!is_register(*str, *i))
		return (token_instr_lab(str, i, row, data));
	end = *i + 1;
	while (ft_isdigit((*str)[end]))
		++end;
	ret = new_token(TOK_REGISTER, *row, *i + 1, data);
	if ((ret->str_val = ft_strndup(*str + *i, end - *i)) == NULL)
	{
		free(ret);
		return (NULL);
	}
	*i = end;
	return (ret);
}

static t_token	*token_direct_label(char **str, int *i, int *row, t_data *data)
{
	t_token *ret;
	int		end;

	end = *i + 2;
	if ((*str)[end] == '\0' || ft_strchr(LABEL_CHARS, (*str)[end]) == NULL)
		return (NULL);
	while ((*str)[end] != '\0'  && ft_strchr(LABEL_CHARS, (*str)[end]) != NULL)
		++end;
	ret = new_token(TOK_DIRECT_LABEL, *row, *i + 1, data);
	if ((ret->str_val = ft_strndup(*str + *i, end - *i)) == NULL)
	{
		free(ret);
		return (NULL);
	}
	*i = end;
	return (ret);
}

static t_token	*token_direct_int(char **str, int *i, int *row, t_data *data)
{
	t_token	*ret;
	int		end;

	end = *i + 1;
	if ((*str)[end] == '-')
		++end;
	if (!ft_isdigit((*str)[end]))
		return (NULL);
	while (ft_isdigit((*str)[end]))
		++end;
	ret = new_token(TOK_DIRECT, *row, *i + 1, data);
	if ((ret->str_val = ft_strndup(*str + *i, end - *i)) == NULL)
	{
		free(ret);
		return (NULL);
	}
	*i = end;
	return (ret);	
}

t_token			*token_direct(char **str, int *i, int *row, t_data *data)
{
	if ((*str)[*i + 1] == '\0')
		return (NULL);
	if ((*str)[*i + 1] == LABEL_CHAR)
		return (token_direct_label(str, i, row, data));
	else if (ft_isdigit((*str)[*i + 1]) || (*str)[*i + 1] == '-')
		return (token_direct_int(str, i, row, data));
	return (NULL);
}
