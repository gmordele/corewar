/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 01:54:29 by gmordele          #+#    #+#             */
/*   Updated: 2017/10/14 02:09:37 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_btree		*btree_create_node(void *item)
{
	t_btree		*new;

	new = malloc(sizeof(t_btree));
	new->left = NULL;
	new->right = NULL;
	new->item = item;
	return (new);
}
