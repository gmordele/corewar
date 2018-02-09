/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 01:07:04 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/25 01:55:14 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char		*ret;
	size_t		i;
	size_t		len;

	len = ft_strlen(s1);
	len = (n < len) ? n : len;
	if ((ret = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s1[i];
		++i;
	}
	ret[i] = '\0';
	return (ret);
}
