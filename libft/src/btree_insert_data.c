/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 02:40:01 by gmordele          #+#    #+#             */
/*   Updated: 2017/10/14 03:14:12 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		btree_insert_data(t_btree **root, void *item,
							int (*cmpt)(void *, void *))
{
	if (*root == NULL)
		*root = btree_create_node(item);
	else if (cmpt(item, (*root)->item) < 0)
		btree_insert_data(&((*root)->left), item, cmpt);
	else
		btree_insert_data(&((*root)->right), item, cmpt);
}
