/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 13:56:32 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/28 20:13:04 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

static int	print_arg(const char **format, va_list *ap)
{
	t_conv_spec		conv_spec;

	parse_conv_spec(format, &conv_spec, ap);
	return (handle_conv_spec(ap, conv_spec));
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	int			ret;
	extern int	g_fd_printf;

	g_fd_printf = 1;
	if (format == NULL)
		return (0);
	ret = 0;
	va_start(ap, format);
	while (*format != '\0')
		if (*format != '%' && *format != '{')
		{
			++ret;
			to_buff(format++, 1);
		}
		else
		{
			if (*(format++) == '%')
				ret += print_arg(&format, &ap);
			else
				ret += handle_color(&format);
		}
	flush_buff();
	va_end(ap);
	return (ret);
}
