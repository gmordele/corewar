/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:36:25 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/17 00:58:29 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char			*ret;
	unsigned int	i;

	ret = (char *)malloc(size + 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i <= size)
		*(ret + i++) = '\0';
	return (ret);
}
