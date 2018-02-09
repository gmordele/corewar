/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:32:41 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/20 04:15:47 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
		write(1, "-", 1);
	if (n < 10 && n > -10)
	{
		c = n < 0 ? -n + '0' : n + '0';
		write(1, &c, 1);
	}
	else
	{
		c = n < 0 ? -(n % 10) + '0' : n % 10 + '0';
		n = n < 0 ? -(n / 10) : n / 10;
		ft_putnbr(n);
		write(1, &c, 1);
	}
}
