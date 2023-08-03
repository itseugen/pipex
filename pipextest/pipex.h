/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:15:58 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/01 13:48:26 by eweiberl         ###   ########.fr       */
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
void	fork_check(pid_t forkid, t_pipe pipe_x);
void	check_arg(int argc, char *argv[]);

#endif