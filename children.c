/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:48:50 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/01 13:43:13 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(int *pipe_fd, t_pipe pipe_x, char *argv[])
{
	close(pipe_fd[0]);
	pipe_x.fd_in = open(argv[1], O_RDONLY);
	if (dup2(pipe_x.fd_in, STDIN_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[1]), clean_exit(pipe_x, 1), 1);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[1]), clean_exit(pipe_x, 1), 1);
	close(pipe_fd[1]);
	if (execute_cmd(argv[2]) == 1)
		clean_exit(pipe_x, 1);
	clean_exit(pipe_x, 0);
	return (0);
}

int	last_child(int *pipe_fd, t_pipe pipe_x, char *argv[], int argc)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[0]), clean_exit(pipe_x, 1), 1);
	if (dup2(pipe_x.fd_out, STDOUT_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[0]), clean_exit(pipe_x, 1), 1);
	close(pipe_fd[0]);
	if (execute_cmd(argv[argc - 2]) == 1)
		clean_exit(pipe_x, 1);
	clean_exit(pipe_x, 0);
	return (0);
}

int	middle_child(int *pipe_fd, t_pipe pipe_x, char *cmd)
{
	// ft_printf("Executing: %s\n", cmd);
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[1]), clean_exit(pipe_x, 1), 1);
	close(pipe_fd[1]);
	if (execute_cmd(cmd) == 1)
		clean_exit(pipe_x, 1);
	clean_exit(pipe_x, 0);
	return (0);
}

// int	middle_child(int *pipe_fd, t_pipe pipe_x, char *cmd)
// {
// 	// ft_printf("Executing: %s\n", cmd);
// 	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 		return (perror("dup2 fail"),
// 			close(pipe_fd[0]), clean_exit(pipe_x, 1), 1);
// 	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// 		return (perror("dup2 fail"),
// 			close(pipe_fd[0]), clean_exit(pipe_x, 1), 1);
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	if (execute_cmd(cmd) == 1)
// 		clean_exit(pipe_x, 1);
// 	clean_exit(pipe_x, 0);
// 	return (0);
// }

// int	middle_child(int *pipe1, int *pipe2, t_pipe pipe_x, char *cmd)
// {
// 	// ft_printf("Executing: %s\n", cmd);
// 	close(pipe2[1]);
// 	close(pipe1[0]);
// 	if (dup2(pipe2[0], STDIN_FILENO) == -1)
// 		return (perror("dup2 fail"), close (pipe1[1]),
// 			close(pipe2[0]), clean_exit(pipe_x, 1), 1);
// 	if (dup2(pipe1[1], STDOUT_FILENO) == -1)
// 		return (perror("dup2 fail"), close (pipe1[1]),
// 			close(pipe2[0]), clean_exit(pipe_x, 1), 1);
// 	close(pipe1[1]);
// 	close(pipe2[0]);
// 	if (execute_cmd(cmd) == 1)
// 		clean_exit(pipe_x, 1);
// 	return (0);
// }

