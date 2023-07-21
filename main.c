/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:19:47 by eweiberl          #+#    #+#             */
/*   Updated: 2023/07/21 16:49:51 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	leaks_check(void)
{
	yellow();
	system("leaks pipex");
	white();
}

int	main(int argc, char *argv[])
{
	t_pipe	pipe;

	atexit(leaks_check);
	if (argc < 5)
		return (0);
	if (argc > 5) /*Remove for bonus*/
		return (0);
	pipe.fd_in = open(argv[1], O_RDONLY);
	pipe.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe.fd_in == -1 || pipe.fd_out == -1)
		return (perror("open"), clean_exit(pipe), 1);
	if (dup2(pipe.fd_in, STDIN_FILENO) == -1)
		return (perror("dup2 fail"), clean_exit(pipe), 1);
	if (dup2(pipe.fd_out, STDOUT_FILENO) == -1)
		return (perror("dup2 fail"), clean_exit(pipe), 1);
	execute_cmd(argv[2]);
	close (pipe.fd_in);
	close (pipe.fd_out);
	return (0);
}

/// @brief Makes a clean exit on an error
/// @param pipe 
void	clean_exit(t_pipe pipe)
{
	close (pipe.fd_in);
	close (pipe.fd_out);
	exit(1);
}

	// int n;
    // int filedes[2];
    // char buffer[1025];
    // char *message = "Hello, World!";
	// atexit(leaks_check);

    // pipe(filedes);
    // write(filedes[1], message, ft_strlen(message));

    // if ((n = read ( filedes[0], buffer, 1024 ) ) >= 0) {
    //     buffer[n] = 0;  //terminate the string
    //     printf("read %d bytes from the pipe: %s\n", n, buffer);
    // }  
    // else
    //     perror("read");
    // exit(0);