/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:16:57 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/17 00:44:15 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	skip(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static void	copy(char *dst, char const *src, unsigned int begin,
				unsigned int end)
{
	while (begin <= end)
		*dst++ = src[begin++];
	*dst = '\0';
}

char		*ft_strtrim(char const *s)
{
	unsigned int	begin;
	unsigned int	end;
	char			*ret;

	if (s == NULL)
		return (NULL);
	end = ft_strlen(s);
	if (end == 0)
		return (ft_strdup(""));
	--end;
	while (end > 0 && skip(s[end]))
		--end;
	if (end == 0 && skip(s[end]))
		return (ft_strdup(""));
	begin = 0;
	while (skip(s[begin]))
		++begin;
	ret = (char *)malloc(end - begin + 2);
	if (ret == NULL)
		return (NULL);
	copy(ret, s, begin, end);
	return (ret);
}
