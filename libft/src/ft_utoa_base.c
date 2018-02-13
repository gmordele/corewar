/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 22:24:25 by edebise           #+#    #+#             */
/*   Updated: 2017/03/07 22:24:27 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa_base(unsigned long nb, int base, char *s)
{
	char	tmp;

	if (!s)
		s = ft_strnew(70);
	if (nb / base)
		ft_utoa_base(nb / base, base, s);
	tmp = nb % base > 9 ? nb % base + 'W' : nb % base + '0';
	ft_strncat(s, &tmp, 1);
	return (s);
}
