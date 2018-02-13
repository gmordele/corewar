/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 02:34:30 by edebise           #+#    #+#             */
/*   Updated: 2017/11/25 02:34:41 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_round_1(char *ptr, int l, int mem)
{
	while (l-- && mem)
	{
		mem = (ptr[l] >= '9' ? 1 : 0);
		ptr[l] += (mem ? -9 : 1);
	}
	return (mem);
}

char		*ft_round(char *s, int precis)
{
	char	*ptr;
	int		l;
	int		mem;

	if (!ft_isdigit(*s) && *s != '-' && *s != '+')
		return (s);
	if (!(ptr = ft_strchr(s, '.')))
		return (precis ? ft_strjf3(s, ".", ft_strnewof(precis, '0'), 13) : s);
	if (precis > (l = ft_strlen(++ptr)))
		return (ft_strjf(s, ft_strnewof(precis - l, '0'), 12));
	if (precis == l)
		return (s);
	l = precis;
	mem = ft_round_1(ptr, l, (ptr[l] >= '5' ? 1 : 0));
	ptr[l] = '\0';
	ptr = (*s == '-' || *s == '+') ? s + 1 : s;
	l = ft_strchr(s, '.') - ptr;
	if (!ft_round_1(ptr, l, mem))
		return (s);
	if (ft_isdigit(*s))
		return (ft_strjf("1", s, 2));
	ptr = (*s == '-' ? "-" : "+");
	*s = '1';
	return (ft_strjf(ptr, s, 2));
}
