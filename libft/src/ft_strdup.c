/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 20:02:50 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/05 20:08:16 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*ret;
	unsigned int	i;

	ret = (char *)malloc(ft_strlen(s1) + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while ((ret[i] = s1[i]) != '\0')
		++i;
	return (ret);
}
