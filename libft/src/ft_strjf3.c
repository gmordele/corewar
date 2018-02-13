/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjf3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 20:29:07 by edebise           #+#    #+#             */
/*   Updated: 2017/01/20 20:29:17 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	jf(int nbfree, int n)
{
	while (nbfree)
	{
		if (n == nbfree % 10)
			return (n);
		nbfree /= 10;
	}
	return (0);
}

char		*ft_strjf3(char *s1, char *s2, char *s3, int nbf)
{
	s1 = (jf(nbf, 1) ? s1 : ft_strjf(s1, NULL, 0));
	s2 = (jf(nbf, 2) ? s2 : ft_strjf(s2, NULL, 0));
	s3 = (jf(nbf, 3) ? s3 : ft_strjf(s3, NULL, 0));
	return (ft_strjf(ft_strjf(s1, s2, 12), s3, 12));
}
