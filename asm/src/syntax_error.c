/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 01:05:59 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/13 01:09:28 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

void	syntax_error(t_token *token, t_data *data)
{
	ft_dprintf(2, "Syntax error at token");
	print_token(2, token);
	ft_dprintf(2, "\n");
	free_token(token);
	err_exit(data);
}
