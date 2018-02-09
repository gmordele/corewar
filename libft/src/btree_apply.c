/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 02:24:13 by gmordele          #+#    #+#             */
/*   Updated: 2017/10/14 02:38:22 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	applyf(root->item);
	if (root->left != NULL)
		btree_apply_prefix(root->left, applyf);
	if (root->right != NULL)
		btree_apply_prefix(root->right, applyf);
}

void		btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root->left != NULL)
		btree_apply_infix(root->left, applyf);
	applyf(root->item);
	if (root->right != NULL)
		btree_apply_infix(root->right, applyf);
}

void		btree_apply_postfix(t_btree *root, void (*applyf)(void *))
{
	if (root->left != NULL)
		btree_apply_postfix(root->left, applyf);
	if (root->right != NULL)
		btree_apply_postfix(root->right, applyf);
	applyf(root->item);
}
