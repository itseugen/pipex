/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:15 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/08 17:11:05 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(t_pipe pipe_x, int argc, char *argv[])
{
	int		pipe_fd[2];
	char	*limit;
	char	*gnl;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe fail"), clean_exit(pipe_x, 1), 1);
	pipe_x.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT);
	if (pipe_x.fd_out == -1)
		return (perror("open"), clean_exit(pipe_x, 1), 1);
	// if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	// 	return (perror("dup2 fail"), clean_exit(pipe_x, 1), 1);
	limit = ft_strjoin(argv[2], "\n");
	gnl = get_next_line(STDIN_FILENO);
	while(ft_strncmp(gnl, limit, ft_strlen(limit)) != 0)
	{
		free(gnl);
		gnl = get_next_line(STDIN_FILENO);
	}
	free(gnl);
	free(limit);
	return (clean_exit(pipe_x, 0), 0);
}
//! Redirect written to pipe, execute cmd like standart_pipe