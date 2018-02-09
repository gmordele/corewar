/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:53:12 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/16 23:24:28 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		if ((*((unsigned char *)dest + i) = *((unsigned char *)src + i))
			== (unsigned char)c)
			return (dest + i + 1);
		++i;
	}
	return (NULL);
}
