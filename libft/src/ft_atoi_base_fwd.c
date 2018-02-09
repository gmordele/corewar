/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_fwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:22:11 by gmordele          #+#    #+#             */
/*   Updated: 2017/02/27 06:06:12 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		get_val(char c, int base)
{
	char	*digit1;
	char	*digit2;
	int		i;

	digit1 = "0123456789ABCDEF";
	i = 0;
	while (i < base && digit1[i] != '\0')
	{
		if (digit1[i] == c)
			return (i);
		++i;
	}
	digit2 = "0123456789abcdef";
	i = 0;
	while (i < base && digit2[i] != '\0')
	{
		if (digit2[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

int				ft_atoi_base_fwd(char **nptr, int base)
{
	int		ret;
	int		sign;
	int		val;

	sign = 1;
	while (**nptr == ' ')
		++(*nptr);
	if (**nptr == '0')
		if (*(*nptr + 1) == 'x')
			*nptr += 2;
	if (**nptr == '-' || **nptr == '+')
	{
		sign = (**nptr == '-') ? -1 : 1;
		++(*nptr);
	}
	ret = 0;
	while ((val = get_val(**nptr, base)) >= 0)
	{
		ret = base * ret + val;
		(*nptr)++;
	}
	return (ret * sign);
}
