/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:15:58 by eweiberl          #+#    #+#             */
/*   Updated: 2023/07/31 12:17:20 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ************************************************************************** */
/*                                Libraries                                   */
/* ************************************************************************** */

# include <stdio.h>
# include <fcntl.h>

# include "libft/libft.h"

/* ************************************************************************** */
/*                                Typedefs                                    */
/* ************************************************************************** */

typedef struct s_pipe
{
	int	fd_in;
	int	fd_out;
}	t_pipe;

/* ************************************************************************** */
/*                                Functions                                   */
/* ************************************************************************** */

int		execute_cmd(char *cmd);
void	clean_exit(t_pipe pipe, int returnval);
int		first_child(int *pipe_fd, t_pipe pipe_x, char *argv[]);
int		last_child(int *pipe_fd, t_pipe pipe_x, char *argv[], int argc);
int		middle_child(int *pipe1, int *pipe2, t_pipe pipe_x, char *cmd);
void	fork_check(pid_t forkid, t_pipe pipe_x);
void	check_arg(int argc, char *argv[]);

#endif