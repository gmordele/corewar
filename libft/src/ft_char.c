/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 12:43:00 by edebise           #+#    #+#             */
/*   Updated: 2018/02/14 12:43:02 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char(int value, int nb_char, ...)
{
	va_list	va;
	char	*c;

	va_start(va, nb_char);
	while (nb_char-- > 0)
		if ((c = (char*)va_arg(va, char*)))
			*c = (char)value;
	va_end(va);
	return (value);
}
