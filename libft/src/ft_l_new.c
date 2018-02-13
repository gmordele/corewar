/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 21:15:54 by edebise           #+#    #+#             */
/*   Updated: 2018/02/06 21:15:56 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_l_new(char *str, void *ptr, int i, long l)
{
	t_lst	*new;

	if (!(new = (t_lst*)ft_malloc(sizeof(t_lst))))
		return (NULL);
	new->str = str;
	new->ptr = ptr;
	new->i = i;
	new->l = l;
	return (new);
}
