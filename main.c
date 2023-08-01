/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:19:47 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/01 13:41:23 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	standart_pipe(t_pipe pipe_x, int argc, char *argv[]);
int	multiple_pipe(t_pipe pipe_x, int argc, char *argv[]);

void	leaks_check(void)
{
	yellow();
	system("leaks pipex");
	white();
}

int	main(int argc, char *argv[])
{
	t_pipe	pipe_x;

	pipe_x.fd_in = open(argv[1], O_RDONLY);
	pipe_x.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe_x.fd_in == -1 || pipe_x.fd_out == -1)
		return (perror("open"), clean_exit(pipe_x, 1), 1);
	check_arg(argc, argv);
	if (argc == 5)
		standart_pipe(pipe_x, argc, argv);
	else if (argc > 5)
		multiple_pipe(pipe_x, argc, argv);
	clean_exit(pipe_x, 0);
	return (0);
}

int	standart_pipe(t_pipe pipe_x, int argc, char *argv[])
{
	int		pipe_fd[2];
	pid_t	pro_id;
	pid_t	pro_id2;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe fail"), 1);
	pro_id = fork();
	fork_check(pro_id, pipe_x);
	if (pro_id == 0)
		first_child(pipe_fd, pipe_x, argv);
	pro_id2 = fork();
	fork_check(pro_id2, pipe_x);
	if (pro_id2 == 0)
		last_child(pipe_fd, pipe_x, argv, argc);
	clean_exit(pipe_x, 0);
	return (0);
}

// int	multiple_pipe(t_pipe pipe_x, int argc, char *argv[])
// {
// 	int		i;
// 	int		pipe_fd[2];
// 	pid_t	pro_id;

// 	i = 3;
// 	if (pipe(pipe_fd) == -1)
// 		return (perror("pipe fail"), 1);
// 	pro_id = fork();
// 	fork_check(pro_id, pipe_x);
// 	if (pro_id == 0)
// 		first_child(pipe_fd, pipe_x, argv);
// 	while (i < argc - 2)
// 	{
// 		pro_id = fork();
// 		fork_check(pro_id, pipe_x);
// 		if (pro_id == 0)
// 			middle_child(pipe_fd, pipe_x, argv[i]);
// 		waitpid(pro_id, NULL, -1);
// 		i++;
// 	}
// 	pro_id = fork();
// 	fork_check(pro_id, pipe_x);
// 	if (pro_id == 0)
// 		last_child(pipe_fd, pipe_x, argv, argc);
// 	return (clean_exit(pipe_x, 0), 0);
// }

/*
Child 1 reads from pipe1 and writes to pipe2, while Child 2
reads from pipe2 and writes to pipe1
*/
// int	multiple_pipe(t_pipe pipe_x, int argc, char *argv[])
// {
// 	int		i;
// 	int		pipe1[2];
// 	int		pipe2[2];
// 	pid_t	pro_id;

// 	i = 3;
// 	if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
// 		return (perror("pipe fail"), 1);
// 	pro_id = fork();
// 	fork_check(pro_id, pipe_x);
// 	if (pro_id == 0)
// 		first_child(pipe2, pipe_x, argv);
// 	while (i < argc - 2)
// 	{
// 		pro_id = fork();
// 		fork_check(pro_id, pipe_x);
// 		if (pro_id == 0)
// 		{
// 			if (i % 2 == 0)
// 				middle_child(pipe2, pipe1, pipe_x, argv[i]);
// 			else
// 				middle_child(pipe1, pipe2, pipe_x, argv[i]);
// 		}
// 		// waitpid(pro_id, NULL, 0);
// 		i++;
// 	}
// 	pro_id = fork();
// 	fork_check(pro_id, pipe_x);
// 	if (pro_id == 0)
// 	{
// 		if ((i - 1) % 2 == 0)
// 			last_child(pipe2, pipe_x, argv, argc);
// 		else
// 			last_child(pipe1, pipe_x, argv, argc);
// 	}
// 	close(pipe1[0]);
// 	close(pipe1[1]);
// 	close(pipe2[0]);
// 	close(pipe2[1]);
// 	return (clean_exit(pipe_x, 0), 0);
// }

int	multiple_pipe(t_pipe pipe_x, int argc, char *argv[])
{
	int		i;
	int		pipe_fd[2];
	pid_t	pro_id;

	i = 3;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe fail"), 1);
	pro_id = fork();
	fork_check(pro_id, pipe_x);
	if (pro_id == 0)
		first_child(pipe_fd, pipe_x, argv);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 fail"), 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	while (i < argc - 2)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe fail"), 1);
		pro_id = fork();
		fork_check(pro_id, pipe_x);
		if (pro_id == 0)
			middle_child(pipe_fd, pipe_x, argv[i]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			return (perror("dup2 fail"), 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		i++;
	}
	pro_id = fork();
	fork_check(pro_id, pipe_x);
	if (pro_id == 0)
		last_child(pipe_fd, pipe_x, argv, argc);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (clean_exit(pipe_x, 0), 0);
}
