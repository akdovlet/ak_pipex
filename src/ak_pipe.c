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
		perror("pipex");
	close(data->hermes);
	if(dup2(fd[1], STDOUT_FILENO) == -1)
		perror("pipex");
	close(fd[1]);
	if (!cmd_exe(data, i))
	{
		ft_free(data->cmd);
		ft_free(data->path);
		exit(127);
	}
}

void	ak_pipe(t_data *data, int i)
{
	int	fd[2];
	int	id;

	if (data->first == -1)
		return ;
	if (pipe(fd) == -1)
		return (perror("pipex"));
	id = fork();
	if (id < 0)
		return (perror("pipex"));
	if (!id)
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
	if (!cmd_exe(data, data->ac - 2))
	{
		ft_free(data->cmd);
		ft_free(data->path);
		exit(127);
	}
}	

int	ak_pipeout(t_data *data)
{
	int	id;

	data->last = open(data->av[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->last < 0)
		return (perror(data->av[data->ac -1]), 1);
	id = fork();
	if (id < 0)
	{
		if (data->last > 0)
			close(data->last);
		if (data->hermes > 0)
			close(data->hermes);
		return (perror("pipex"), -1);
	}
	if (!id)
		child_out(data);
	close(data->hermes);
	close(data->last);
	wait(NULL);
	wait(NULL);
	return (0);
}
