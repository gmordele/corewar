/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_5_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 00:13:48 by edebise           #+#    #+#             */
/*   Updated: 2017/11/28 00:13:51 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pf.h"

int		fpf(int fd, const char *restrict format, ...)
{
	t_pf	o;

	va_start(o.va, format);
	pf_begin(&o, ft_strdup(format), fd);
	va_end(o.va);
	return (o.ret);
}

char	*spf(const char *restrict format, ...)
{
	t_pf	o;

	va_start(o.va, format);
	o.ret_s = NULL;
	pf_begin(&o, ft_strdup(format), -1);
	va_end(o.va);
	return (o.ret_s);
}
