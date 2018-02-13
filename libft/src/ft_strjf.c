/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 22:05:57 by edebise           #+#    #+#             */
/*   Updated: 2017/01/20 22:05:59 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjf(char *s1, char *s2, int nbfree)
{
	char	*new;

	if (!s1 && !s2)
		return (ft_strnew(0));
	if (!s1 || !s2)
		new = (!s1 ? ft_strdup(s2) : ft_strdup(s1));
	else
	{
		new = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		ft_strcpy(new, s1);
		ft_strcat(new, s2);
	}
	(s1 && (nbfree == 1 || nbfree > 2)) ? free(s1) : 0;
	(s2 && (nbfree == 2 || nbfree > 2)) ? free(s2) : 0;
	return (new);
}
