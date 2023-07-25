/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:48:50 by eweiberl          #+#    #+#             */
/*   Updated: 2023/07/25 17:15:14 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(int *pipe_fd, t_pipe pipe_x, char *argv[])
{
	close(pipe_fd[0]);
	pipe_x.fd_in = open(argv[1], O_RDONLY);
	if (dup2(pipe_x.fd_in, STDIN_FILENO) == -1)
		return (perror("dup2 fail"), close(pipe_fd[1]), clean_exit(pipe_x), 1);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2 fail"), close(pipe_fd[1]), clean_exit(pipe_x), 1);
	close(pipe_fd[1]);
	execute_cmd(argv[2]);
	clean_exit(pipe_x);
	return (0);
}

int	last_child(int *pipe_fd, t_pipe pipe_x, char *argv[])
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 fail"), close(pipe_fd[0]), clean_exit(pipe_x), 1);
	if (dup2(pipe_x.fd_out, STDOUT_FILENO) == -1)
		return (perror("dup2 fail"), close(pipe_fd[0]), clean_exit(pipe_x), 1);
	close(pipe_fd[0]);
	execute_cmd(argv[3]);
	clean_exit(pipe_x);
	return (0);
}
