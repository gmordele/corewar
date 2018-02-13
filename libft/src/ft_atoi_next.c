/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 02:32:25 by edebise           #+#    #+#             */
/*   Updated: 2017/11/25 02:32:31 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_next(char **ptr)
{
	char	*s;
	int		sign;
	int		nb;

	nb = 0;
	sign = 1;
	if (ptr && (s = *ptr))
	{
		while (ft_isspc(*s))
			s++;
		if (*s == '+' || (*s == '-' && (sign = -1)))
			s++;
		if (ft_isdigit(*s) && (*ptr = s))
			while (ft_isdigit(**ptr))
			{
				nb = nb * 10 + (**ptr - '0');
				(*ptr)++;
			}
	}
	return (nb * sign);
}
