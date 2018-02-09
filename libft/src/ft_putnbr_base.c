/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 07:45:22 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/26 08:02:22 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_base(int n, int base)
{
	char		c;
	static char	digits[] = "0123456789abcdef";

	if (n < 0)
		write(1, "-", 1);
	if (n < base && n > -base)
	{
		c = digits[n < 0 ? -n : n];
		write(1, &c, 1);
	}
	else
	{
		c = digits[n < 0 ? -(n % base) : n % base];
		n = n < 0 ? -(n / base) : n / base;
		ft_putnbr_base(n, base);
		write(1, &c, 1);
	}
}
