/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:16:00 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/04 15:40:25 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd(char *cmd, t_pipe pipe_x)
{
	char	*cmds[4];

	cmds[0] = "/bin/sh";
	cmds[1] = "-c";
	cmds[2] = cmd;
	cmds[3] = NULL;
	if (execve("/bin/sh", cmds, pipe_x.envp) == -1)
		return (perror("execv"), 1);
	return (0);
}
