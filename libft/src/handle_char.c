/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 05:28:31 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/16 15:16:21 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

int		handle_char(char conv, va_list *ap, t_conv_spec cs)
{
	char	*buff;
	int		len;

	buff = NULL;
	if (cs.length == 'l' || conv == 'C')
		len = buff_wchar(&buff, (wint_t)va_arg(*ap, wint_t), cs);
	else if (cs.conv == 'c')
		len = buff_char(&buff, (char)va_arg(*ap, int), cs);
	else
		len = buff_char(&buff, '%', cs);
	if (buff != NULL)
	{
		to_buff(buff, len);
		free(buff);
	}
	return (buff != NULL ? len : 0);
}
