/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 11:34:44 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/25 13:00:25 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	free_string(char *s1, char *s2, int free_choice)
{
	if (free_choice & 1)
		free(s1);
	if (free_choice & 2)
		free(s2);
}

char		*ft_strjoinfree(char *s1, char *s2, int free_choice)
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
	free_string(s1, s2, free_choice);
	return (ret);
}
