/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:19:47 by eweiberl          #+#    #+#             */
/*   Updated: 2023/08/01 15:04:00 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	get_cmd_len(int argc, char *argv[]);
char	*get_cmd_line(int argc, char *argv[], size_t cmd_len);

void	leaks_check(void)
{
	yellow();
	system("leaks pipex");
	white();
}

int	main(int argc, char *argv[])
{
	size_t	cmd_len;
	char	*cmd_line;

	check_arg(argc, argv);
	cmd_len = get_cmd_len(argc, argv);
	cmd_line = get_cmd_line(argc, argv, cmd_len);
	if (cmd_line == NULL)
		return (perror("malloc fail"), 1);
	if (execute_cmd(cmd_line) == 1)
		return (free(cmd_line), perror("execve fail"), 1);
	return (0);
}

size_t	get_cmd_len(int argc, char *argv[])
{
	size_t	len;
	int		i;

	i = 2;
	len = 3;
	len = len + ft_strlen(argv[1]) + 1;
	while (i < argc - 1)
	{
		len = len + ft_strlen(argv[i]) + 3;
		i++;
	}
	len = len + ft_strlen(argv[argc - 1]);
	return (len);
}

char	*get_cmd_line(int argc, char *argv[], size_t cmd_len)
{
	char	*cmd_line;
	int		i;

	i = 2;
	cmd_line = ft_calloc(cmd_len, sizeof(char));
	if (cmd_line == NULL)
		return (NULL);
	ft_strlcat(cmd_line, "< ", cmd_len);
	ft_strlcat(cmd_line, argv[1], cmd_len);
	ft_strlcat(cmd_line, " ", cmd_len);
	while (i < argc - 2)
	{
		ft_strlcat(cmd_line, argv[i], cmd_len);
		ft_strlcat(cmd_line, " | ", cmd_len);
		i++;
	}
	ft_strlcat(cmd_line, argv[i], cmd_len);
	ft_strlcat(cmd_line, " > ", cmd_len);
	ft_strlcat(cmd_line, argv[argc - 1], cmd_len);
	return (cmd_line);
}
