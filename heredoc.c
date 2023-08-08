/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:15 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/08 16:25:07 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(t_pipe pipe_x, int argc, char *argv)
{
	pipe_x.fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT);
	if (pipe_x.fd_out == -1)
		return (perror("open"), clean_exit(pipe_x, 1), 1);
	
}
