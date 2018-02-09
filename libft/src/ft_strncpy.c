/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 20:23:54 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/05 20:34:38 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	unsigned int i;

	i = 0;
	while (i < len)
	{
		if ((dest[i] = src[i]) == '\0')
			while (i < len)
				dest[i++] = '\0';
		++i;
	}
	return (dest);
}
