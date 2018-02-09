/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:36:35 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/17 01:12:09 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (len--)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
