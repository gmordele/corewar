/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:46:09 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/10 17:07:05 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static size_t	ft_buff_len(char *s, size_t size)
{
	size_t	len;

	len = 0;
	while (*s++ && size--)
		++len;
	return (len);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	n;

	src_len = ft_strlen(src);
	dst_len = ft_buff_len(dst, size);
	n = dst_len;
	if (size > 0)
		while (n < size - 1 && *src)
		{
			dst[n++] = *src++;
			dst[n] = '\0';
		}
	return (src_len + dst_len);
}
