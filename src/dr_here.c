/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dr_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:17:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/15 03:36:38 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dr_dre(t_data *data, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			clear_exit(data, EXIT_FAILURE);
		if (!ft_strncmp(line, data->av[2], ft_strlen(data->av[2])))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	dr_here(t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		clear_exit(data, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		clear_exit(data, EXIT_FAILURE);
	if (!pid)
		dr_dre(data, fd);
	else
	{
		close(fd[1]);
		data->hermes = fd[0];
		waitpid(pid, &status, 0);
		data->exit_code = WEXITSTATUS(status);
	}
}
