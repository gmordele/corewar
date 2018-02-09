/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 19:07:35 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/17 19:10:06 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void			*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned int	i;

	if (src < dest)
	{
		i = len;
		while (i > 0)
		{
			--i;
			((char *)dest)[i] = ((char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((char *)dest)[i] = ((char *)src)[i];
			++i;
		}
	}
	return (dest);
}
