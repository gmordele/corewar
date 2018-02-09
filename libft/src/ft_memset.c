/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:22:46 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/05 18:31:52 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int		i;
	char				*p;

	p = (char *)b;
	i = 0;
	while (i < len)
		p[i++] = (char)c;
	return (b);
}
