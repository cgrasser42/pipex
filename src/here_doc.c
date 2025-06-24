/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:33:28 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/24 10:50:44 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	read_stdin(int *fd, char *limiter)
{
	char	*line;
	int		c;

	c = ft_strlen(limiter);
	close(fd[0]);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, limiter, c) && line[c] == '\n')
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_printf(fd[1], line);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	exit(EXIT_SUCCESS);
}

void	here_doc(char *limiter)
{
	pid_t	reader;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_error("pipe() failed");
	reader = fork();
	if (reader == 0)
		read_stdin(fd, limiter);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}
