/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_1_get_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:54:08 by edebise           #+#    #+#             */
/*   Updated: 2018/02/13 13:54:12 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm_0.h"

int		vm_get_champ_nb(t_all *all, int *n, char **av)
{
	int		champ_nb;
	long	l;
	char	*s;

	champ_nb = 0;
	if (!ft_strcmp(av[*n], "-n"))
	{
		s = av[++n[0]];
		l = (s ? ft_atol(s) : 0);
		champ_nb = (s ? ft_atoi_next(&s) : 0);
		if (!s || *s || champ_nb < 1 || champ_nb != l)
		{
			fpf(2, "corewar: '%s' is not a valid champ number\n", av[*n]);
			vm_usage(all);
		}
		n[0]++;
	}
	return (champ_nb);
}

void	vm_get_champ_path(t_all *all, int *n, char **av)
{
	int		champ_nb;
	int		path_len;
	int		fd;
	char	*s;

	champ_nb = vm_get_champ_nb(all, n, av);
	path_len = (av[*n] ? ft_strlen(av[*n]) : 0);
	fd = 0;
	if (path_len > 4)
	{
		s = av[*n] + path_len - 4;
		if (!ft_strcmp(s, ".cor"))
			fd = open(av[*n], O_RDONLY);
	}
	if (fd < 1)
	{
		fpf(2, "corewar: '%s' is not a valid champ path\n", av[*n]);
		vm_usage(all);
	}
	vm_l_add_frt(&all->champs, vm_l_new(all, av[*n], fd, champ_nb));
}

void	vm_get_dump(t_all *all, int *n, char **av)
{
	int		i;
	long	l;
	char	*s;

	all->dump = 0;
	if ((s = av[++n[0]]))
	{
		l = ft_atol(s);
		i = ft_atoi_next(&s);
		if (!*s && i > 0 && i == l)
			all->dump = i;
	}
	if (!all->dump)
	{
		fpf(2, "corewar: '%s' is not a valid dump number\n", av[*n]);
		vm_usage(all);
	}
}

void	vm_get_flag(t_all *all, int *n, char **av)
{
	if (!ft_strcmp(av[*n], "-help") || !ft_strcmp(av[*n], "--help"))
		vm_usage(all);
	else if (!ft_strcmp(av[*n], "-dump") || !ft_strcmp(av[*n], "--dump"))
		vm_get_dump(all, n, av);
	else if (!ft_strcmp(av[*n], "-visu") || !ft_strcmp(av[*n], "--visu"))
		all->flag += (all->flag & VISU ? 0 : VISU);
	else
	{
		fpf(2, "corewar: '%s' is not a valid flag\n", av[*n]);
		vm_usage(all);
	}
}
