/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:14:09 by edebise           #+#    #+#             */
/*   Updated: 2017/01/23 17:14:14 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_f_multi2(unsigned int *tab0, int *len, unsigned long mantisse)
{
	int	l;

	l = len[1];
	while (l-- > 0)
	{
		tab0[-1] += (*tab0 * 2) / 1000000000;
		*tab0 = ((*tab0 * 2) % 1000000000);
		tab0++;
	}
	if (mantisse & 0x8000000000000000)
		tab0[-1] += 1;
	if (tab0[-1 - len[1]])
		len[1]++;
	l = len[1];
	while (l-- > 0 && tab0--)
	{
		tab0[-1] += tab0[0] / 1000000000;
		*tab0 = *tab0 % 1000000000;
	}
}

void	ft_f_divis2(unsigned int *tab, int *len, unsigned long mantisse)
{
	unsigned int	*tab2;
	unsigned int	*tab4;
	int				l;

	tab4 = tab + len[4] + len[5];
	if ((l = len[5]))
		while (l-- > 0)
		{
			tab4[1] += (*tab4 & 1 ? 500000000 : 0);
			*tab4-- /= 2;
		}
	else
		tab4[1] = 500000000;
	if (tab4[len[5] + 1])
		len[5]++;
	tab2 = tab + len[2];
	tab4 = tab + len[4];
	if ((mantisse & 0x8000000000000000) && ft_int(len[5], 2, len + 3, &l))
		while (l-- > 0)
		{
			*tab2 += (tab2[1] + tab4[1]) / 1000000000;
			tab2++;
			tab4++;
			*tab2 = (*tab2 + *tab4) % 1000000000;
		}
}

char	*ft_ftoa_string(int sign, unsigned int *tab, int *len)
{
	unsigned int	*tmp;
	char			*str;
	char			*s;
	int				i;

	if (!(str = ft_strnew(5 + (len[1] * 9) + (len[3] * 9))))
		return (NULL);
	s = (sign ? ft_strcat(str, "-") + 1 : str);
	ft_utoa_base(tab[len[0] - len[1]--], 10, s);
	s = ft_strchr(s, 0) - 1;
	tmp = tab + len[0];
	while (len[1]-- > 0 && (i = 9) && tmp--)
		while (i && (s[(len[1] * 9) + i--] = (*tmp % 10) + '0'))
			*tmp /= 10;
	s = ft_strchr(ft_strcat(s, "."), '.');
	tmp = tab + len[2] + (len[3] ? len[3] : len[3]++) + 1;
	while (len[3]-- && (i = 9) && tmp--)
		while (i && (s[(len[3] * 9) + i--] = (*tmp % 10) + '0'))
			*tmp /= 10;
	s = ft_strchr(s, 0) - 1;
	while (s[0] == '0' && s[-1] != '.')
		*s-- = '\0';
	return (str);
}

char	*ft_ftoa_1(int sign, unsigned long mantisse, int exp, int *len)
{
	unsigned int	tab[len[0] + (2 * len[4])];

	ft_bzero(tab, sizeof(int) * (len[0] + (2 * len[4])));
	len[4] += len[2];
	while (exp >= 0)
	{
		ft_f_multi2(tab + len[0] - len[1], len, mantisse);
		mantisse <<= 1;
		exp--;
	}
	while (exp++ < -1)
		ft_f_divis2(tab, len, 0);
	while (mantisse)
	{
		ft_f_divis2(tab, len, mantisse);
		mantisse <<= 1;
	}
	return (ft_ftoa_string(sign, tab, len));
}

char	*ft_ftoa(long double ld)
{
	int				exp;
	unsigned long	mantisse;
	int				len[6];

	if (!ld)
		return (ft_strdup("0.0"));
	mantisse = *((unsigned long*)(&ld));
	exp = *((unsigned short*)(&ld) + 4);
	if (ld != ld)
		return (ft_strdup("nan"));
	if ((exp & 0x7fff) == 0x7fff)
		return (ft_strdup(exp & 0x8000 ? "-inf" : "inf"));
	exp -= (exp & 0x8000 ? 0xbfff : 0x3fff);
	ft_bzero(len, 24);
	len[0] = 4 + (exp < 0 ? 0 : (exp / 3) / 8);
	len[2] = len[0];
	len[4] = 9 + (exp < 0 ? 2 + ((-exp) / 8) : 0);
	return (ft_ftoa_1((ld < 0 ? 1 : 0), mantisse, exp, len));
}
