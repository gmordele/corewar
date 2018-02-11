/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 01:25:57 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/11 05:44:29 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "stdlib.h"
#include "libft.h"
#include "asm.h"

void	err_exit(t_data *data)
{
	(void)data;
	free_data(data);
	exit(EXIT_FAILURE);
}

void	err_exit_str(char *str, t_data *data)
{
	ft_dprintf(2, "%s\n", str);
	err_exit(data);
}

void	err_exit_strerror(char *str, t_data *data)
{
	ft_dprintf(2, "%s: %s\n", str, strerror(errno));
	err_exit(data);
}
