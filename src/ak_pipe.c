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

void	child(int fd[2], t_data *data)
{
	close(fd[0]);
	if (dup2(data->hermes, STDIN_FILENO) == -1)
		return (perror("pipex"), clear_exit(data, EXIT_FAILURE));
	close(data->hermes);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (perror("pipex"), clear_exit(data, EXIT_FAILURE));
	close(fd[1]);
	cmd_exe(data);
}

void	ak_pipe(t_data *data, int i)
{
	int	fd[2];

	if (data->first == -1 && i == 2)
		return ;
	if (pipe(fd) == -1)
		return (perror("pipex"), clear_exit(data, EXIT_FAILURE));
	data->ids[i - (2 + data->here_doc)] = fork();
	if (data->ids[i - (2 + data->here_doc)] < 0)
		return (perror("pipex"), clear_exit(data, EXIT_FAILURE));
	if (!data->ids[i - (2 + data->here_doc)])
		child(fd, data);
	close(fd[1]);
	close(data->hermes);
	data->hermes = fd[0];
}
