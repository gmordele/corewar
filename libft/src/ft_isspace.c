/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 03:25:47 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/24 03:27:04 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r' || c == ' ');
}
