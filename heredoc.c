/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:15 by eweiberl          #+#    #+#             */
/*   Updated: 2023/09/12 18:00:44 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	first_child_here_doc(int *pipe_fd, t_pipe pipe_x, char *argv[]);
static int	last_child_here_doc(int *pipe_fd, t_pipe pipe_x,
				char *argv[], int argc);
static int	read_terminal(char *argv[], int *pipe_fd, t_pipe pipe_x);

int	here_doc(t_pipe pipe_x, int argc, char *argv[])
{
	int		pipe_fd[2];
	int		pipe2_fd[2];
	pid_t	pro_id;
	pid_t	pro_id2;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe fail"), clean_exit(pipe_x, 1), 1);
	pipe_x.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
	if (pipe_x.fd_out == -1)
		return (perror("open"), clean_exit(pipe_x, 1), 1);
	read_terminal(argv, pipe_fd, pipe_x);
	if (pipe(pipe2_fd) == -1)
		return (perror("pipe fail"), clean_exit(pipe_x, 1), 1);
	pro_id = fork();
	fork_check(pro_id, pipe_x);
	if (pro_id == 0)
		first_child_here_doc(pipe2_fd, pipe_x, argv);
	pro_id2 = fork();
	fork_check(pro_id2, pipe_x);
	if (pro_id2 == 0)
		last_child_here_doc(pipe2_fd, pipe_x, argv, argc);
	close(pipe2_fd[0]);
	close(pipe2_fd[1]);
	wait(NULL);
	return (wait(NULL), clean_exit(pipe_x, 0), 0);
}

static int	read_terminal(char *argv[], int *pipe_fd, t_pipe pipe_x)
{
	char	*limit;
	char	*gnl;

	limit = ft_strjoin(argv[2], "\n");
	if (limit == NULL)
		return (perror("malloc fail"), clean_exit(pipe_x, 1), 1);
	gnl = get_next_line(STDIN_FILENO);
	while (gnl != NULL && ft_strncmp(gnl, limit, ft_strlen(limit) + 1) != 0)
	{
		write(pipe_fd[1], gnl, ft_strlen(gnl));
		free(gnl);
		gnl = get_next_line(STDIN_FILENO);
	}
	close(pipe_fd[1]);
	if (gnl != NULL)
		free(gnl);
	free(limit);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 fail"), clean_exit(pipe_x, 1), 1);
	close(pipe_fd[0]);
	return (0);
}

static int	first_child_here_doc(int *pipe_fd, t_pipe pipe_x, char *argv[])
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2 fail"),
			close(pipe_fd[1]), clean_exit(pipe_x, 1), 1);
	close(pipe_x.fd_in);
	close(pipe_x.fd_out);
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
	close(pipe_x.fd_in);
	close(pipe_x.fd_out);
	close(pipe_fd[0]);
	if (execute_cmd(argv[argc - 2], pipe_x) == 1)
		clean_exit(pipe_x, 1);
	clean_exit(pipe_x, 0);
	return (0);
}
