/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:35:16 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/17 01:11:03 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len;
	char			*ret;
	unsigned int	i;
	unsigned int	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		ret[j++] = s1[i++];
	i = 0;
	while ((ret[j++] = s2[i++]))
		;
	return (ret);
}
