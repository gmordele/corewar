/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_0_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:32:09 by edebise           #+#    #+#             */
/*   Updated: 2018/02/27 21:16:40 by proso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_0.h"

/*
**	vm_exit()
**	quit properly program by freeing memory from t_all structure
**	write an error_mail in stderr if an error_mail is define
*/

int		vm_exit(t_all *all, char *error_mail)
{
	vm_del_all_pro(&all->process_list);
	while (all->nb_champ-- > 0)
		close(all->champ[all->nb_champ].fd);
	if (all->flag & VISU)
		vm_exit_visu(all);
	if (error_mail)
		fpf(2, "{r}%s{0}", error_mail);
	exit(0);
	return (0);
}

/*
**	vm_usage()
**	write usage of the executable in stderr
**	write an error_mail in stderr if an error_mail is define
**	quit properly program with vm_exit()
*/

void	vm_usage(t_all *all, char *error_mail)
{
	if (error_mail)
	{
		fpf(2, "{y}%s{0}", error_mail);
		ft_free(1, &error_mail);
	}
	fpf(2, "usage:\tcorewar [--help] [--visu] [[--dump | -d] nb_cycles]");
	fpf(2, " [-n champ_nb] champ.cor ...\n");
	fpf(2, "\t--help: display the usage you're looking at\n");
	fpf(2, "\t--visu: execute corewar with a visual tool\n");
	fpf(2, "\t--dump: set number of cycles, must be followed by a int\n");
	fpf(2, "\t-n: set number of the following champ in params\n");
	fpf(2, "\t    must be followed by an int and a champ.cor\n");
	fpf(2, "\t    otherwise, corewar set this number in order of params\n");
	fpf(2, "\t    last player process will be execute in first\n");
	vm_exit(all, 0);
}

/*
**	vm_malloc()
**	allocate memory with ft_malloc (as memalloc)
**	if malloc returns NULL, quit properly program with vm_exit()
*/

void	*vm_malloc(t_all *all, int size)
{
	void *ptr;

	if (!(ptr = (void*)ft_malloc(size)))
		vm_exit(all, "Error of malloc\n");
	return (ptr);
}

/*
**	vm_init()
**	initialize t_all structure with bzero
**	getting flags and champ_path in params
**	if it is needed, quit with vm_usage()
**	allocate memory to arena (char tab) and color (char tab)
*/

void	vm_init(t_all *all, int ac, char **av)
{
	int		n;

	ft_bzero(all, sizeof(t_all));
	n = 0;
	while (++n < ac)
	{
		if (av[n][0] != '-' || !ft_strcmp(av[n], "-n"))
			vm_get_champ_path(all, &n, av);
		else
			vm_get_flag(all, &n, av);
	}
	if (!all->nb_champ || !all->champ[0].fd)
		vm_usage(all, spf("corewar: no champ enough\n"));
	all->cycle_to_die = CYCLE_TO_DIE;
	if (all->flag & DUMP)
		all->flag = DUMP;
	else
		all->dump = 0x7fffffff;
	if (all->flag & VISU)
		vm_init_visu(all);
}

/*
**	main()
**	run corewar by calling primary fonctions for each big step
**		read params
**		get champs binary files
**		set arena and process
**		run the battle in arena
**		quit program when the fight is done
*/

int		main(int ac, char **av)
{
	t_all	all;

	vm_init(&all, ac, av);
	vm_get_champs(&all, sizeof(t_header));
	vm_set_match(&all);
	vm_run_battle(&all);
	vm_print_winner(&all);
	vm_exit(&all, NULL);
	return (0);
}
