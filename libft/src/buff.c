/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 05:06:22 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/28 20:13:12 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

static char	g_buff[BUF_SIZE_PF];
static int	g_pos = 0;
int			g_fd_printf = 1;

void	to_buff(const char *s, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (g_pos == BUF_SIZE_PF)
		{
			flush_buff(g_pos);
			g_buff[0] = s[i];
			g_pos = 1;
		}
		else
			g_buff[g_pos++] = s[i];
		++i;
	}
}

void	flush_buff(void)
{
	write(g_fd_printf, g_buff, g_pos);
	g_pos = 0;
}
