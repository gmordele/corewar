/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_0_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebise <edebise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 20:32:09 by edebise           #+#    #+#             */
/*   Updated: 2018/02/11 20:32:16 by edebise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vm_0.h"

int		vm_exit(t_all *all, char *error_mail)
{
	if (error_mail)
		fpf(2, error_mail);
	vm_l_del(&all->champs);
	/*ft_free();
	ft_l_del(&all->...);*/
	(void)all;
	exit(0);
	return (0);
}

void	vm_usage(t_all *all)
{
	fpf(2, "usage:\tcorewar [--help] [--visu] [--dump nb_cycles] [-n] champ.cor ...\n");
	fpf(2, "\t--help: display the usage you're looking at\n");
	fpf(2, "\t--visu: execute corewar with a visual tool\n");
	fpf(2, "\t--dump: set number of cycles, must be followed by a reasonable int\n");
	fpf(2, "\t-n: set number of the following champ in params\n");
	fpf(2, "\t    must be followed by an int and a champ.cor\n");
	fpf(2, "\t    otherwise, corewar set this number in order of params\n");
	fpf(2, "\t    last player process will be execute in first\n");
	vm_exit(all, 0);
}

void	*vm_malloc(t_all *all, int size)
{
	void *ptr;

	if (!(ptr = (void*)ft_malloc(size)))
		vm_exit(all, "Error of malloc\n");
	return (ptr);
}

void	vm_init(t_all *all, int ac, char **av)
{
	int		n;

	ft_int(0, 3, &all->nb_champs, &all->flag, &all->dump);
	ft_ptr(NULL, 1, &all->champs);
	n = 0;
	while (++n < ac)
	{
		if (av[n][0] != '-' || !ft_strcmp(av[n], "-n"))
			vm_get_champ_path(all, &n, av);
		else
			vm_get_flag(all, &n, av);
	}
	if (!all->champs)
	{
		fpf(2, "corewar: no champ enough\n");
		vm_usage(all);
	}
}

int		main(int ac, char **av)
{
	t_all	all;

	vm_init(&all, ac, av);
	vm_get_champs(&all, sizeof(t_header));
	return (0);
}
