/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 20:49:10 by gmordele          #+#    #+#             */
/*   Updated: 2016/11/05 21:08:56 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		++i;
	while (j < n && (s1[i] = s2[j]) != '\0')
	{
		++i;
		++j;
	}
	if (j == n)
		s1[i] = '\0';
	return (s1);
}
