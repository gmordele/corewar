/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capital.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:58:55 by edebise           #+#    #+#             */
/*   Updated: 2017/01/21 19:58:57 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_capital(char *str)
{
	if (str && *str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		ft_capital(str + 1);
	}
	return (str);
}