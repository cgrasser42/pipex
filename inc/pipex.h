/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 23:28:42 by cgrasser          #+#    #+#             */
/*   Updated: 2025/06/24 11:05:53 by cgrasser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file pipex.h
 * @brief Header file for pipex project, handling pipeline creation,
 * command execution, and file management.
 *
 * This header defines the functions, macros,
 * and constants used in the pipex project.
 * It provides declarations for command pipeline management, error handling,
 * file opening with different modes, and here_doc input processing.
 */

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

/**
 * @brief Handles here_doc mode by setting up a pipe and reading input
 *        until a delimiter is found.
 *
 * Creates a pipe and forks a child process. The child reads from standard input
 * until it reaches the given limiter string.
 * The parent then connects the read endof the pipe to its standard input.
 *
 * @param limiter   The delimiter string marking the end of input.
 *
 * @note Calls exit_error() and terminates if pipe creation fails.
 */
void	here_doc(char *limiter);

/**
 * @brief Runs a sequence of piped commands from argv[start] to argv[end - 1].
 *
 * Calls pipe_process() for each intermediate command.
 * Standard input is updated between calls via dup2().
 *
 * @param av Argument vector (commands).
 * @param env Environment variables.
 * @param start Index of the first command to execute.
 * @param end Index *after* the last command to execute (exclusive).
 */
void	run_pipeline(char **av, char **env, int start, int end);

/**
 * @brief Executes a single command using execve().
 *
 * Splits the command string, resolves the executable path,
 * and runs it with execve().
 *
 * @param av Command string (e.g. "grep something").
 * @param env Environment variables.
 *
 * @note Exits the program if the command cannot be found or execve fails.
 */
void	execute(char *av, char **env);

/**
 * @brief Opens a file with the given mode and returns its file descriptor.
 *
 * This function opens the file in one of the following modes:
 * - opt == 0 → write with append (`O_WRONLY | O_CREAT | O_APPEND`)
 * - opt == 1 → write with truncate (`O_WRONLY | O_CREAT | O_TRUNC`)
 * - opt == 2 → read only (`O_RDONLY`)
 *
 * If the file can't be opened, it calls `exit_error()` with the file name.
 *
 * @param file The name/path of the file to open.
 * @param opt  The mode to open the file:
 *             - 0: append
 *             - 1: truncate
 *             - 2: read-only
 * @return The file descriptor of the opened file.
 *
 * @note The program exits on error, so no -1 is returned.
 */
int		open_file(char *file, int opt);

/**
 * @brief Prints a system error message and exits the program with failure.
 *
 * Uses perror() to display the error message prefixed by `error_msg`,
 * then terminates the program with EXIT_FAILURE.
 *
 * @param error_msg The message to print before the system error description.
 */
void	exit_error(char *error_msg);

#endif