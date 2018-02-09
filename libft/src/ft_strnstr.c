/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:50:00 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/17 00:01:38 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*p1;
	char	*p2;
	size_t	little_len;

	if (*little == '\0')
		return ((char *)big);
	little_len = ft_strlen(little);
	while (*big && len >= little_len)
	{
		if (*big == *little)
		{
			p1 = (char *)big;
			p2 = (char *)little;
			while (*p1 == *p2 && *p2 != '\0')
			{
				++p1;
				++p2;
			}
			if (*p2 == '\0')
				return ((char *)big);
		}
		--len;
		++big;
	}
	return (NULL);
}
