/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:29:21 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/10 17:47:53 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *big, const char *little)
{
	char	*p1;
	char	*p2;

	if (*little == '\0')
		return ((char *)big);
	while (*big)
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
		++big;
	}
	return (NULL);
}
