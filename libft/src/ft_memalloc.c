/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:31:33 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/12 16:31:34 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void			*ret;
	unsigned int	i;

	ret = malloc(size);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		*((char *)ret + i++) = 0;
	return (ret);
}
