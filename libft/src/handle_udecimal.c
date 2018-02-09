/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_udecimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 23:17:13 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/22 22:40:13 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

int		handle_udecimal(char conv, va_list *ap, t_conv_spec cs)
{
	char	*buff;
	int		len;

	buff = NULL;
	if (cs.length == 'l' || conv == 'U')
		len = ulong_udec_itoa(&buff, va_arg(*ap, unsigned long), cs);
	else if (conv == 'u' && cs.length == 0)
		len = udec_itoa(&buff, (unsigned)va_arg(*ap, unsigned), cs);
	else if (cs.length == 'H')
		len = udec_itoa(&buff, (unsigned char)va_arg(*ap, unsigned), cs);
	else if (cs.length == 'h')
		len = udec_itoa(&buff, (unsigned short)va_arg(*ap, unsigned), cs);
	else if (cs.length == 'L')
		len = ullong_udec_itoa(&buff, va_arg(*ap, unsigned long long), cs);
	else if (cs.length == 'j')
		len = ullong_udec_itoa(&buff, va_arg(*ap, uintmax_t), cs);
	else if (cs.length == 'z')
		len = ullong_udec_itoa(&buff, va_arg(*ap, size_t), cs);
	if (buff != NULL)
	{
		to_buff(buff, len);
		free(buff);
	}
	return (buff != NULL ? len : 0);
}
