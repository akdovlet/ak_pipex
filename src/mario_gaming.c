/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mario_gaming.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:33:16 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/07 02:21:34 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	mario_gaming(t_data *data, int i)
{
	int	fd[2];
	int	id;

	if (pipe(fd) == -1)
		return (perror("pipex"));
	id = fork();
	if (id < 0)
		return (perror("pipex"));
	if (!id)
	{
		close(fd[0]);
		if (dup2(data->hermes, STDIN_FILENO) == -1)
		{
			perror("pipex2");
			close(data->hermes);
		}
		close(data->hermes);
		if(dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("pipex2");
			close(fd[1]);
		}
		close(fd[1]);
		cmd_exe(data, i);
	}
	else
	{
		close(fd[1]);
		data->hermes = fd[0];
		wait(NULL);
	}
}

int	get_out(t_data *data)
{
	int	id;

	data->last = open(data->av[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->last < 0)
		perror("pipex3");
	id = fork();
	if (id < 0)
		return (perror("pipex4"), close(data->last), -1);
	if (!id)
	{
		dup2(data->hermes, STDIN_FILENO);
		close(data->hermes);
		dup2(data->last, STDOUT_FILENO);
		close(data->last);
		cmd_exe(data, data->ac - 2);
	}
	else
	{
		close(data->hermes);
		close(data->last);
		wait(NULL);
	}
	return (0);
}
