/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:54:08 by gmordele          #+#    #+#             */
/*   Updated: 2018/03/06 16:54:20 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "asm.h"

void			free_token(t_token *token)
{
	if (token == NULL)
		return ;
	if (token->str_val != NULL)
		free(token->str_val);
	free(token);
}
