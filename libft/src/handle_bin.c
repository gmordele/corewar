/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 22:36:21 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/22 22:36:23 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "ft_printf.h"

int		handle_bin(va_list *ap, t_conv_spec cs)
{
	char	*buff;
	int		len;

	buff = NULL;
	if (cs.length == 0)
		len = bin_itoa(&buff, (unsigned)va_arg(*ap, unsigned), cs);
	else if (cs.length == 'l')
		len = ulong_bin_itoa(&buff, va_arg(*ap, unsigned long), cs);
	else if (cs.length == 'H')
		len = bin_itoa(&buff, (unsigned char)va_arg(*ap, unsigned), cs);
	else if (cs.length == 'h')
		len = bin_itoa(&buff, (unsigned short)va_arg(*ap, unsigned), cs);
	else if (cs.length == 'L')
		len = ullong_bin_itoa(&buff, va_arg(*ap, unsigned long long), cs);
	else if (cs.length == 'j')
		len = ullong_bin_itoa(&buff, va_arg(*ap, uintmax_t), cs);
	else if (cs.length == 'z')
		len = ullong_bin_itoa(&buff, va_arg(*ap, size_t), cs);
	if (buff != NULL)
	{
		to_buff(buff, len);
		free(buff);
	}
	return (buff != NULL ? len : 0);
}
