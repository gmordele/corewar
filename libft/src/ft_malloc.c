/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:59:13 by edebise           #+#    #+#             */
/*   Updated: 2018/01/30 16:59:15 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_malloc(int size)
{
	void *tab;

	if (size < 1 || !(tab = (void*)malloc(size)))
		return (NULL);
	while (size-- > 0)
		((char*)tab)[size] = 0;
	return (tab);
}
