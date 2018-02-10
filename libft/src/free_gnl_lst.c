/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gnl_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 20:27:17 by gmordele          #+#    #+#             */
/*   Updated: 2018/01/31 22:19:52 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	del(void *content, size_t size)
{
	t_fd_buff	*fd_buff;

	(void)size;
	fd_buff = content;
	if (fd_buff != NULL)
	{
		if (fd_buff->buff != NULL)
			free(fd_buff->buff);
		free(fd_buff);
	}
}

int			free_gnl_lst(t_list **lst)
{
	ft_lstdel(lst, &del);
	return (0);
}
