/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 01:41:06 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/17 18:16:11 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		get_nwords(char const *s, char c)
{
	int nwords;

	nwords = 0;
	while (*s != '\0')
	{
		while (*s == c)
			++s;
		if (*s != '\0')
		{
			++nwords;
			while (*s != c && *s != '\0')
				++s;
		}
	}
	return (nwords);
}

static size_t	get_word_len(char const *s, char c)
{
	size_t len;

	len = 0;
	while (*s != '\0' && *s != c)
	{
		++len;
		++s;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		nwords;
	int		i;
	size_t	word_len;

	if (s == NULL)
		return (NULL);
	nwords = get_nwords(s, c);
	ret = (char **)malloc(sizeof(char *) * (nwords + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (nwords--)
	{
		while (*s == c)
			++s;
		word_len = get_word_len(s, c);
		ret[i++] = ft_strsub(s, 0, word_len);
		s += word_len;
	}
	ret[i] = 0;
	return (ret);
}
