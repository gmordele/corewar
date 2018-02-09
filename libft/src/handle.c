/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:36:43 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/22 22:28:59 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int				handle_conv_spec(va_list *ap, t_conv_spec cs)
{
	if (cs.conv == 'd' || cs.conv == 'D' || cs.conv == 'i')
		return (handle_decimal_int(cs.conv, ap, cs));
	else if (cs.conv == 'o' || cs.conv == 'O' || cs.conv == 'x'
		|| cs.conv == 'X' || cs.conv == 'u' || cs.conv == 'U' || cs.conv == 'p'
		|| cs.conv == 'b')
		return (handle_unsigned_int(cs.conv, ap, cs));
	else if (cs.conv == 'c' || cs.conv == 'C' || cs.conv == '%')
		return (handle_char(cs.conv, ap, cs));
	else if (cs.conv == 's' || cs.conv == 'S')
		return (handle_string(cs.conv, ap, cs));
	if (cs.conv == '\0')
		return (1);
	to_buff(&cs.conv, 1);
	return (2);
}
