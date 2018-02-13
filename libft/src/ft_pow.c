/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 18:16:44 by edebise           #+#    #+#             */
/*   Updated: 2017/11/25 18:16:50 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_pow(long nb, int power)
{
	if (power > 0)
		return (nb * ft_pow(nb, power - 1));
	else if (power < 0)
		return (1 / ft_pow(nb, -power));
	return (1);
}
