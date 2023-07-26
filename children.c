/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:48:50 by eweiberl          #+#    #+#             */
/*   Updated: 2023/07/26 14:01:58 by eweiberl         ###   ########.fr       */
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

int	last_child(int *pipe_fd, t_pipe pipe_x, char *argv[])
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[0]), clean_exit(pipe_x, 1), 1);
	if (dup2(pipe_x.fd_out, STDOUT_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[0]), clean_exit(pipe_x, 1), 1);
	close(pipe_fd[0]);
	if (execute_cmd(argv[3]) == 1)
		clean_exit(pipe_x, 1);
	clean_exit(pipe_x, 0);
	return (0);
}
