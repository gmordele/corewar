/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_0_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 00:12:28 by edebise           #+#    #+#             */
/*   Updated: 2017/11/28 00:12:33 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pf.h"

void	pf_init_s(t_pf *o)
{
	o->s_pfx = o->buf + PF_SIZE + 1;
	o->s_ptr = o->s_pfx + 5;
	o->s_len = 0;
	ft_bzero(o->s_pfx, 10);
}

void	pf_buf_empty(t_pf *o, int fd)
{
	o->buf[o->buf_len] = '\0';
	if (fd >= 0)
		write(fd, o->buf, o->buf_len);
	else
		o->ret_s = ft_strjf(o->ret_s, o->buf, 1);
	o->ret += o->buf_len;
	o->buf_len = 0;
}

int		pf_buf_ncat(t_pf *o, char *s, char c, int n)
{
	int	ret;

	ret = 0;
	if (s)
		while (*s && n--)
		{
			if (o->buf_len == PF_SIZE)
				pf_buf_empty(o, o->fd);
			o->buf[o->buf_len++] = *s++;
			ret++;
		}
	else
		while (n--)
		{
			if (o->buf_len == PF_SIZE)
				pf_buf_empty(o, o->fd);
			o->buf[o->buf_len++] = c;
			ret++;
		}
	return (ret);
}
