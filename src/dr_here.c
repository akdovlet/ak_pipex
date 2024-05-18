/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dr_here.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:17:44 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/18 20:52:21 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	delimiter_cmp(char *s1, char *s2)
{
	int	i;

	i = -1;
	while ((s1[++i] || s2[i]) && s2[i] != '\n')
		if (s1[i] != s2[i])
			return (false);
	if (s2[i] == '\n' && s2[i + 1] == '\0')
		if (s1[i] == '\0')
			return (true);
	return (false);
}

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
		if (delimiter_cmp(data->here_doc_delimiter, line))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	clear_exit(data, EXIT_SUCCESS);
}

void	dr_here(t_data *data)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		clear_exit(data, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		clear_exit(data, EXIT_FAILURE);
	if (pid == CHILD)
		dr_dre(data, fd);
	else
	{
		close(fd[1]);
		data->hermes = fd[0];
		waitpid(pid, &status, 0);
		data->exit_code = WEXITSTATUS(status);
	}
}
