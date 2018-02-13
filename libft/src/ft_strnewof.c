/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnewof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 18:34:48 by edebise           #+#    #+#             */
/*   Updated: 2017/01/20 18:34:53 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnewof(size_t size, char c)
{
	char *new;

	if (!(new = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	new[size] = '\0';
	ft_memset(new, c, size);
	return (new);
}
