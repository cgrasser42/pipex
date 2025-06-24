/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 06:10:02 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/24 10:32:33 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

int	open_file(char *file, int opt)
{
	int	fd;

	fd = 0;
	if (opt == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (opt == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (opt == 2)
		fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		exit_error(file);
	return (fd);
}
