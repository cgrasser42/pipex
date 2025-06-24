/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:47:16 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/24 10:51:40 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	usage(void)
{
	ft_printf(1, "usage: %s\n", USAGE);
	ft_printf(1, "       %s\n", USAGE_HERE_DOC);
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	int	fd_in;
	int	fd_out;
	int	i;

	if (ac < 5)
		usage();
	if (!ft_strcmp(av[1], "here_doc"))
	{
		if (ac < 6)
			usage();
		i = 3;
		here_doc(av[2]);
		fd_out = open_file(av[ac -1], APPEND);
	}
	else
	{
		i = 2;
		fd_in = open_file(av[1], 2);
		fd_out = open_file(av[ac - 1], 1);
		dup2(fd_in, STDIN_FILENO);
	}
	run_pipeline(av, env, i, ac -2);
	dup2(fd_out, STDOUT_FILENO);
	execute(av[ac -2], env);
	return (0);
}
