/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 00:28:40 by gmordele          #+#    #+#             */
/*   Updated: 2017/10/15 00:28:42 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		btree_free(t_btree **root, void (*del)(void *))
{
	if ((*root)->left != NULL)
		btree_free(&((*root)->left), del);
	if ((*root)->right != NULL)
		btree_free(&((*root)->right), del);
	del((*root)->item);
	free(*root);
	*root = NULL;
}
