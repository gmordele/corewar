/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 17:47:58 by edebise           #+#    #+#             */
/*   Updated: 2018/01/21 17:47:58 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(int nb_ptr, ...)
{
	va_list	va;
	char	**ptr;

	va_start(va, nb_ptr);
	while (nb_ptr-- > 0)
		if ((ptr = (char**)va_arg(va, char**)) && *ptr)
		{
			free(*ptr);
			*ptr = NULL;
		}
	va_end(va);
}
