/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 22:37:07 by gmordele          #+#    #+#             */
/*   Updated: 2017/03/22 22:39:09 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	print_res(const char **format)
{
	to_buff(COL_RES, 4);
	*format += 4;
	return (4);
}

int			handle_color(const char **ft)
{
	if (ft_strnequ(*ft, "RES}", 4))
		return (print_res(ft));
	else if (ft_strnequ(*ft, "BLA}", 4) || ft_strnequ(*ft, "RED}", 4) ||
		ft_strnequ(*ft, "GRE}", 4) || ft_strnequ(*ft, "YEL}", 4))
		return (print_col1(ft));
	else if (ft_strnequ(*ft, "BLU}", 4) || ft_strnequ(*ft, "MAG}", 4) ||
		ft_strnequ(*ft, "CYA}", 4) || ft_strnequ(*ft, "WHI}", 4))
		return (print_col2(ft));
	else if (ft_strnequ(*ft, "BG_BLA}", 7) || ft_strnequ(*ft, "BG_RED}", 7) ||
			ft_strnequ(*ft, "BG_GRE}", 7) || ft_strnequ(*ft, "BG_YEL}", 7))
		return (print_col3(ft));
	else if (ft_strnequ(*ft, "BG_BLU}", 7) || ft_strnequ(*ft, "BG_MAG}", 7) ||
			ft_strnequ(*ft, "BG_CYA}", 7) || ft_strnequ(*ft, "BG_WHI}", 7))
		return (print_col4(ft));
	to_buff("{", 1);
	return (1)	;
}
