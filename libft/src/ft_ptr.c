/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 17:46:22 by edebise           #+#    #+#             */
/*   Updated: 2018/01/21 17:46:24 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_ptr(void *address, int nb_ptr, ...)
{
	va_list	va;
	char	**ptr;

	va_start(va, nb_ptr);
	while (nb_ptr-- > 0)
		if ((ptr = (char**)va_arg(va, char**)))
			*ptr = (char*)address;
	va_end(va);
	return (address);
}
