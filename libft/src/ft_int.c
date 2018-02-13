/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 17:45:51 by edebise           #+#    #+#             */
/*   Updated: 2018/01/21 17:45:53 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int(int value, int nb_int, ...)
{
	va_list	va;
	int		*i;

	va_start(va, nb_int);
	while (nb_int-- > 0)
		if ((i = (int*)va_arg(va, int*)))
			*i = value;
	va_end(va);
	return (value);
}
