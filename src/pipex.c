/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 06:09:59 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/24 10:47:20 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ":");
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	return (free(paths), NULL);
}

static void	pipe_process(char *cmd, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit_error("pipe() failed");
	pid = fork();
	if (pid == -1)
		exit_error("fork() failed");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(cmd, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	run_pipeline(char **av, char **env, int start, int end)
{
	while (start < end)
		pipe_process(av[start++], env);
}

void	execute(char *av, char **env)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	cmd = ft_split(av, " ");
	path = find_path(cmd[0], env);
	if (!path)
	{
		perror(cmd[0]);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, env) == -1)
		exit_error("execve() failed");
}
