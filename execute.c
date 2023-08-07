/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:16:00 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/07 14:00:29 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(t_pipe pipe_x);
static void	free_split(char **split);
static char	*get_shell(char *path_var, char *shell_path);

int	execute_cmd(char *cmd, t_pipe pipe_x)
{
	char	*cmds[4];

	pipe_x.shell = get_path(pipe_x);
	if (pipe_x.shell == NULL)
		return (perror("getting path"), 1);
	cmds[0] = pipe_x.shell;
	cmds[1] = "-c";
	cmds[2] = cmd;
	cmds[3] = NULL;
	if (execve(pipe_x.shell, cmds, pipe_x.envp) == -1)
		return (free(pipe_x.shell), perror("execv"), 1);
	free(pipe_x.shell);
	return (0);
}

static char	*get_path(t_pipe pipe_x)
{
	char	*path_var;
	char	*shell_path;
	int		i;

	i = 0;
	path_var = NULL;
	shell_path = NULL;
	while (pipe_x.envp[i] != NULL)
	{
		if (ft_strncmp(pipe_x.envp[i], "PATH=", 5) == 0)
		{
			path_var = pipe_x.envp[i] + 5;
			break ;
		}
		i++;
	}
	if (path_var == NULL)
		return (NULL);
	return (get_shell(path_var, shell_path));
}

static char	*get_shell(char *path_var, char *shell_path)
{
	char	**dir;
	char	buf[1024];
	int		i;

	dir = NULL;
	dir = ft_split(path_var, ':');
	if (dir == NULL)
		return (perror("ft_split fail"), NULL);
	i = 0;
	while (dir[i] != NULL)
	{
		ft_strlcpy(buf, dir[i], 1024);
		ft_strlcat(buf, "/sh", 1024);
		if (access(buf, X_OK) == 0)
		{
			shell_path = ft_strdup(buf);
			break ;
		}
		i++;
	}
	i = 0;
	free_split(dir);
	return (shell_path);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
