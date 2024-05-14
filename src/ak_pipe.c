/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ak_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:33:16 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/12 14:42:07 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(int fd[2], t_data *data, int i)
{
	close(fd[0]);
	if (dup2(data->hermes, STDIN_FILENO) == -1)
		return (perror("pipex"), clear_exit(data, EXIT_FAILURE));
	close(data->hermes);
	if(dup2(fd[1], STDOUT_FILENO) == -1)
		return (perror("pipex"), clear_exit(data, EXIT_FAILURE));
	close(fd[1]);
	cmd_exe(data, i);
}

void	ak_pipe(t_data *data, int i)
{
	int	fd[2];

	if (data->first == -1 && i == 2)
		return ;
	if (pipe(fd) == -1)
		return (perror("pipex"), clear_exit(data, EXIT_FAILURE));
	data->ids[i - 2] = fork();
	if (data->ids[i - 2] < 0)
		return (perror("pipex"), clear_exit(data, EXIT_FAILURE));
	if (!data->ids[i - 2])
		child(fd, data, i);
	close(fd[1]);
	close(data->hermes);
	data->hermes = fd[0];
}

void	child_out(t_data *data)
{
	if (dup2(data->hermes, STDIN_FILENO) == -1)
		perror("pipex");
	close(data->hermes);
	if (dup2(data->last, STDOUT_FILENO) == -1)
		perror("pipex");
	close(data->last);
	cmd_exe(data, data->ac - 2);
}	

void	ak_pipeout(t_data *data, int i)
{
	int status;
	int	j;

	j = 0;
	data->last = open(data->av[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->last < 0)
		return (perror(data->av[data->ac -1]), clear_all(data), exit(EXIT_FAILURE));
	data->ids[i - 2] = fork();
	if (data->ids[i - 2] < 0)
	{
		clear_all(data);
		return (perror("pipex"));
	}
	if (!data->ids[i - 2])
		child_out(data);
	close(data->first);
	close(data->hermes);
	while (j < data->ac - 3)
	{
		if (waitpid(data->ids[j],&status, 0) == -1)
			perror("waitpid");
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		j++;
	}
}
