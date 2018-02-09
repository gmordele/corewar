/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 18:00:17 by gmordele          #+#    #+#             */
/*   Updated: 2017/01/30 21:12:35 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				handle_unsigned_int(char conv, va_list *ap, t_conv_spec cs)
{
	if (conv == 'o' || conv == 'O')
		return (handle_octal(conv, ap, cs));
	else if (conv == 'u' || conv == 'U')
		return (handle_udecimal(conv, ap, cs));
	else if (conv == 'x' || conv == 'X')
		return (handle_hex(ap, cs));
	else if (conv == 'p')
		return (handle_pointer(ap, cs));
	else if (conv == 'b')
		return (handle_bin(ap, cs));
	return (0);
}
