/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:28:42 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/24 10:50:50 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

# include <fcntl.h>
# include <sys/wait.h>

# define INPUT 0
# define OUTPUT 1
# define APPEND 2

# define USAGE "./pipex <file1> <cmd> <cmd> <...> <file2>"
# define USAGE_HERE_DOC "./pipex here_doc <LIMITER> <cmd> <cmd> <...> <file>"

void	here_doc(char *limiter);
void	run_pipeline(char **av, char **env, int start, int end);
void	execute(char *av, char **env);

int     open_file(char *file, int opt);
void	exit_error(char *error_msg);

#endif