/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:09:12 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/01 14:54:48 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
}