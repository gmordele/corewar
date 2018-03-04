/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_1_get_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:54:08 by edebise           #+#    #+#             */
/*   Updated: 2018/02/27 21:18:38 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_get_champ_nb()
**	define champ_nb to 0 if no flag '-n'
**	otherwise, get champ_nb with the following param
**		the program quits with vm_usage() if:
**			the param is not an int
**			another champ has the same int
*/

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
		if (!s || *s || !champ_nb || champ_nb != l)
			vm_usage(all, spf("corewar: '%s' is not a valid champ number\n",
			av[*n]));
		if (champ_nb == all->champ[0].nb || champ_nb == all->champ[1].nb
			|| champ_nb == all->champ[2].nb)
			vm_usage(all, spf("corewar: many champs have the same nb '%s'\n",
			av[*n]));
		n[0]++;
	}
	return (champ_nb);
}

/*
**	vm_get_champ_path()
**	function called for each champ path in av[]
**	define a champ_nb with vm_get_champ_nb()
**	the champ path is checked
**		if it is a .cor extension
**		if open(path) works
**	otherwise, the program quits with vm_usage()
*/

void	vm_get_champ_path(t_all *all, int *n, char **av)
{
	all->champ[all->nb_champ].nb = vm_get_champ_nb(all, n, av);
	if (all->nb_champ >= MAX_PLAYERS)
		vm_exit(all, "Too much champ_path in params\n");
	all->champ[all->nb_champ].path = av[*n];
	if (av[*n] && (!ft_strstr(av[*n], ".cor")
		|| ft_strcmp(av[*n] + ft_strlen(av[*n]) - 4, ".cor")))
		vm_usage(all, spf("corewar: '%s' has not a .cor extention\n", av[*n]));
	all->champ[all->nb_champ].fd = open(av[*n], O_RDONLY);
	if (all->champ[all->nb_champ].fd < 1)
		vm_usage(all, spf("corewar: '%s' is not a valid path\n", av[*n]));
	all->nb_champ++;
}

/*
**	vm_get_dump()
**	function called after flag DUMP
**	get value of all->dump in param after DUMP
**	if the value is not valid, the program quits with vm_usage()
*/

void	vm_get_dump(t_all *all, int *n, char **av)
{
	int		i;
	long	l;
	char	*s;

	all->dump = -1;
	if ((s = av[++n[0]]))
	{
		l = ft_atol(s);
		i = ft_atoi_next(&s);
		if (!*s && i == l)
			all->dump = i;
	}
	if (all->dump < 0)
		vm_usage(all, spf("corewar: '%s' i'snt a valid dump number\n", av[*n]));
	all->flag += (all->flag & DUMP ? 0 : DUMP);
}

/*
**	vm_get_flag()
**	function called if av[*n] begin with '-'
**	get flag if av[*n] is a valid flag string
**	otherwise, the program quits with vm_usage()
*/

void	vm_get_flag(t_all *all, int *n, char **av)
{
	if (!ft_strcmp(av[*n], "-help") || !ft_strcmp(av[*n], "--help"))
		vm_usage(all, 0);
	else if (!ft_strcmp(av[*n], "-d") || !ft_strcmp(av[*n], "--dump"))
		vm_get_dump(all, n, av);
	else if (!ft_strcmp(av[*n], "-visu") || !ft_strcmp(av[*n], "--visu"))
		all->flag += (all->flag & VISU ? 0 : VISU);
	else if (!ft_strcmp(av[*n], "-a") || !ft_strcmp(av[*n], "--aff"))
		all->flag += (all->flag & AFF ? 0 : AFF);
	else
		vm_usage(all, spf("corewar: '%s' is not a valid flag\n", av[*n]));
}
