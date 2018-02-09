/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:00:14 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/23 05:15:38 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"

int		handle_pointer(va_list *ap, t_conv_spec cs)
{
	char	*buff;
	int		len;

	buff = NULL;
	len = pointer_itoa(&buff, (unsigned long)va_arg(*ap, void *), cs);
	if (buff != NULL)
	{
		to_buff(buff, len);
		free(buff);
	}
	return (buff != NULL ? len : 0);
}
