/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:16:00 by eweiberl          #+#    #+#             */
/*   Updated: 2023/07/27 15:45:39 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd(char *cmd)
{
	char	*cmds[4];

	cmds[0] = "/bin/sh";
	cmds[1] = "-c";
	cmds[2] = cmd;
	cmds[3] = NULL;
	if (execve("/bin/sh", cmds, NULL) == -1)
		return (perror("execv"), 1);
	return (0);
}
