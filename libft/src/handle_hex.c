/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 23:19:14 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/22 22:39:52 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

int		handle_hex(va_list *ap, t_conv_spec cs)
{
	char	*buff;
	int		len;

	buff = NULL;
	if (cs.length == 0)
		len = hex_itoa(&buff, (unsigned)va_arg(*ap, unsigned), cs);
	else if (cs.length == 'H')
		len = hex_itoa(&buff, (unsigned char)va_arg(*ap, unsigned), cs);
	else if (cs.length == 'h')
		len = hex_itoa(&buff, (unsigned short)va_arg(*ap, unsigned), cs);
	else if (cs.length == 'l')
		len = ulong_hex_itoa(&buff, va_arg(*ap, unsigned long), cs);
	else if (cs.length == 'L')
		len = ullong_hex_itoa(&buff, va_arg(*ap, unsigned long long), cs);
	else if (cs.length == 'j')
		len = ullong_hex_itoa(&buff, va_arg(*ap, uintmax_t), cs);
	else if (cs.length == 'z')
		len = ullong_hex_itoa(&buff, va_arg(*ap, size_t), cs);
	if (buff != NULL)
	{
		to_buff(buff, len);
		free(buff);
	}
	return (buff != NULL ? len : 0);
}
