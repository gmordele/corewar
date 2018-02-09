/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:25:16 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/12 16:26:41 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n'
			|| c == '\r' || c == '\t' || c == '\v');
}

int			ft_atoi(const char *nptr)
{
	int	ret;
	int	sign;

	sign = 1;
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '-' || *nptr == '+')
	{
		sign = *nptr == '-' ? -1 : 1;
		++nptr;
	}
	ret = 0;
	while (*nptr >= '0' && *nptr <= '9')
		ret = 10 * ret + *nptr++ - '0';
	return (ret * sign);
}
