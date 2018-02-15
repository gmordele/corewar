/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_endian.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:21:25 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/15 11:45:24 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			reverse_endian_int(int	n)
{
	int		ret;
	((char *)(&ret))[0] = ((char *)(&n))[3];
	((char *)(&ret))[1] = ((char *)(&n))[2];
	((char *)(&ret))[2] = ((char *)(&n))[1];
	((char *)(&ret))[3] = ((char *)(&n))[0];
	return (ret);
}

short		reverse_endian_short(short n)
{
	short		ret;
	((char *)(&ret))[0] = ((char *)(&n))[1];
	((char *)(&ret))[1] = ((char *)(&n))[0];
	return (ret);
}
