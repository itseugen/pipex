/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:19:47 by eweiberl          #+#    #+#             */
/*   Updated: 2023/07/26 16:55:13 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_arg(int argc, char *argv[]);

void	leaks_check(void)
{
	yellow();
	system("leaks pipex");
	white();
}

int	main(int argc, char *argv[])
{
	t_pipe	pipe_x;
	int		pipe_fd[2];
	pid_t	pro_id;
	pid_t	pro_id2;

	check_arg(argc, argv);
	pipe_x.fd_in = open(argv[1], O_RDONLY);
	pipe_x.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe_x.fd_in == -1 || pipe_x.fd_out == -1)
		return (perror("open"), clean_exit(pipe_x, 1), 1);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe fail"), 1);
	pro_id = fork();
	fork_check(pro_id, pipe_x);
	if (pro_id == 0)
		first_child(pipe_fd, pipe_x, argv);
	else
	{
		pro_id2 = fork();
		fork_check(pro_id2, pipe_x);
		if (pro_id2 == 0)
			last_child(pipe_fd, pipe_x, argv);
	}
	clean_exit(pipe_x, 0);
	return (0);
}

/// @brief Makes a clean exit on an error
/// @param pipe 
void	clean_exit(t_pipe pipe, int returnval)
{
	if (pipe.fd_in != -1)
		close (pipe.fd_in);
	if (pipe.fd_out != -1)
		close (pipe.fd_out);
	exit(returnval);
}

void	check_arg(int argc, char *argv[])
{
	(void)argv;
	if (argc < 5)
		exit(0);
	if (argc > 5)
		exit (0);
}

/// @brief Checks for fork fail
/// @param forkid 
/// @param pipe_x 
void	fork_check(pid_t forkid, t_pipe pipe_x)
{
	if (forkid == -1)
	{
		perror("fork fail");
		clean_exit(pipe_x, 1);
	}
}

/*
int	main(int argc, char *argv[])
{
	t_pipe	pipe_x;
	int		pipe_fd[2];
	pid_t	pro_id;

	atexit(leaks_check);
	if (argc < 5)
		return (0);
	if (argc > 5)
		return (0);
	pipe_x.fd_in = open(argv[1], O_RDONLY);
	pipe_x.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe_x.fd_in == -1 || pipe_x.fd_out == -1)
		return (perror("open"), clean_exit(pipe_x), 1);
	if (pipe(pipe_fd) == -1)
		return (perror("pipe fail"), 1);
	pro_id = fork();
	if (pro_id == -1)
		return (perror("fork fail"), 1);
	if (pro_id == 0) //!Child procress
	{
		close(pipe_fd[0]);
		pipe_x.fd_in = open(argv[1], O_RDONLY);
		if (dup2(pipe_x.fd_in, STDIN_FILENO) == -1)
			return (perror("dup2 fail"), close(pipe_fd[1]), clean_exit(pipe_x), 1);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			return (perror("dup2 fail"), close(pipe_fd[1]), clean_exit(pipe_x), 1);
		close(pipe_fd[1]);
		execute_cmd(argv[2]);
	}
	else //!Parent process
	{
		close(pipe_fd[1]);
		wait(NULL);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (perror("dup2 fail"), close(pipe_fd[0]), clean_exit(pipe_x), 1);
		if (dup2(pipe_x.fd_out, STDOUT_FILENO) == -1)
			return (perror("dup2 fail"), close(pipe_fd[0]), clean_exit(pipe_x), 1);
		execute_cmd(argv[3]);
		close(pipe_fd[0]);
	}
	close(pipe_x.fd_in);
	close(pipe_x.fd_out);
	return (0);
}
*/