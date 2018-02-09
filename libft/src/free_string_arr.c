/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 01:42:06 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/28 01:50:48 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_string_arr(char **arr)
{
	char **p;

	if (arr == NULL)
		return ;
	p = arr;
	while (*p != NULL)
	{
		free(*p);
		++p;
	}
	free(arr);
}
