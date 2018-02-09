/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_decimal_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 17:56:38 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/01 14:42:22 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int				handle_decimal_int(char conv, va_list *ap, t_conv_spec cs)
{
	char	*buff;
	int		len;

	buff = NULL;
	if (cs.length == 'l' || conv == 'D')
		len = long_decimal_itoa(&buff, va_arg(*ap, long), cs);
	else if (cs.length == 0)
		len = decimal_itoa(&buff, va_arg(*ap, int), cs);
	else if (cs.length == 'H')
		len = decimal_itoa(&buff, (signed char)va_arg(*ap, int), cs);
	else if (cs.length == 'h')
		len = decimal_itoa(&buff, (short)va_arg(*ap, int), cs);
	else if (cs.length == 'L')
		len = llong_decimal_itoa(&buff, va_arg(*ap, long long), cs);
	else if (cs.length == 'j')
		len = llong_decimal_itoa(&buff, va_arg(*ap, intmax_t), cs);
	else if (cs.length == 'z')
		len = llong_decimal_itoa(&buff, va_arg(*ap, size_t), cs);
	if (buff != NULL)
	{
		to_buff(buff, len);
		free(buff);
	}
	return (buff != NULL ? len : 0);
}
