/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 03:18:33 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/11 04:09:51 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "asm.h"
#include "op.h"

static int	is_register(char *str, int i)
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

t_token		*token_register(char **str, int *i, int *row, t_data *data)
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
