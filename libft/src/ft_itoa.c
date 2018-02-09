/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:30:50 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/12 16:38:27 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_get_len(int n)
{
	size_t	len;

	len = n < 0 ? 1 : 0;
	while (n)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static void		ft_fill_ret(char *ret, int n, size_t len)
{
	ret[len] = '\0';
	if (n < 0)
		ret[0] = '-';
	while (n)
	{
		if (n > 0)
		{
			ret[--len] = n % 10 + '0';
			n /= 10;
		}
		else
		{
			ret[--len] = -(n % 10) + '0';
			n /= -10;
		}
	}
}

char			*ft_itoa(int n)
{
	char	*ret;
	size_t	len;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_get_len(n);
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	ft_fill_ret(ret, n, len);
	return (ret);
}
