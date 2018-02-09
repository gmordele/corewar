/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 07:28:56 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/26 07:41:41 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_base_fd(int n, int base, int fd)
{
	char		c;
	static char	digits[] = "0123456789abcdef";

	if (n < 0)
		write(fd, "-", 1);
	if (n < base && n > -base)
	{
		c = digits[n < 0 ? -n : n];
		write(fd, &c, 1);
	}
	else
	{
		c = digits[n < 0 ? -(n % base) : n % base];
		n = n < 0 ? -(n / base) : n / base;
		ft_putnbr_base_fd(n, base, fd);
		write(fd, &c, 1);
	}
}
