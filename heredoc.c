/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:15 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/09 14:23:35 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	first_child_here_doc(int *pipe_fd, t_pipe pipe_x, char *argv[]);
static int	last_child_here_doc(int *pipe_fd, t_pipe pipe_x,
				char *argv[], int argc);

int	here_doc(t_pipe pipe_x, int argc, char *argv[])
{
	int		pipe_fd[2];
	char	*limit;
	char	*gnl;
	pid_t	pro_id;
	pid_t	pro_id2;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe fail"), clean_exit(pipe_x, 1), 1);
	pipe_x.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT);
	if (pipe_x.fd_out == -1)
		return (perror("open"), clean_exit(pipe_x, 1), 1);
	limit = ft_strjoin(argv[2], "\n");
	gnl = get_next_line(STDIN_FILENO);
	if (limit == NULL || gnl == NULL)
		return (perror("malloc fail"), free(gnl), free(limit), clean_exit(pipe_x, 1), 1);
	while (ft_strncmp(gnl, limit, ft_strlen(limit)) != 0 && gnl != NULL)
	{
		write(pipe_fd[1], gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(STDIN_FILENO);
	}
	free(gnl);
	free(limit);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 fail"), clean_exit(pipe_x, 1), 1);
	pro_id = fork();
	fork_check(pro_id, pipe_x);
	if (pro_id == 0)
		first_child_here_doc(pipe_fd, pipe_x, argv);
	pro_id2 = fork();
	fork_check(pro_id2, pipe_x);
	if (pro_id2 == 0)
		last_child_here_doc(pipe_fd, pipe_x, argv, argc);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	wait(NULL);
	return (clean_exit(pipe_x, 0), 0);
}
//! Redirect written to pipe, execute cmd like standart_pipe

static int	first_child_here_doc(int *pipe_fd, t_pipe pipe_x, char *argv[])
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[1]), clean_exit(pipe_x, 1), 1);
	close(pipe_fd[1]);
	if (execute_cmd(argv[3], pipe_x) == 1)
		clean_exit(pipe_x, 1);
	clean_exit(pipe_x, 0);
	return (0);
}

static int	last_child_here_doc(int *pipe_fd, t_pipe pipe_x,
				char *argv[], int argc)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[0]), clean_exit(pipe_x, 1), 1);
	if (dup2(pipe_x.fd_out, STDOUT_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[0]), clean_exit(pipe_x, 1), 1);
	close(pipe_fd[0]);
	if (execute_cmd(argv[argc - 2], pipe_x) == 1)
		clean_exit(pipe_x, 1);
	clean_exit(pipe_x, 0);
	return (0);
}
