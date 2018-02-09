/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:35:37 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/12 20:39:41 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t			len;
	unsigned int	i;
	char			*ret;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = f(s[i]);
		++i;
	}
	ret[i] = '\0';
	return (ret);
}
