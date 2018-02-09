/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 16:03:30 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/01 14:46:04 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"
#include <wchar.h>
#include "libft.h"

int				handle_string(char conv, va_list *ap, t_conv_spec cs)
{
	char	*buff;
	int		len;

	buff = NULL;
	if (cs.length == 'l' || conv == 'S')
		len = buff_strwch(&buff, (wchar_t *)va_arg(*ap, wchar_t *), cs);
	else
		len = buff_string(&buff, (char *)va_arg(*ap, char *), cs);
	if (buff != NULL)
	{
		to_buff(buff, len);
		free(buff);
	}
	return (buff != NULL ? len : 0);
}
