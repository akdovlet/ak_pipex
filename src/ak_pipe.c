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

void	ak_pipe(t_data *data, int i)
{
	int	fd[2];

	if (data->infile == -1 && i == 0)
		return ;
	if (pipe(fd) == -1)
		return (perror("pipe"), clear_all_exit(data, EXIT_FAILURE));
	data->pid_array[i] = fork();
	if (data->pid_array[i] < 0)
		return (perror("fork"), clear_all_exit(data, EXIT_FAILURE));
	if (data->pid_array[i] == CHILD)
		child(fd, data);
	close(fd[1]);
	close(data->hermes);
	data->hermes = fd[0];
}

void	child(int fd[2], t_data *data)
{
	close(fd[0]);
	if (dup2(data->hermes, STDIN_FILENO) == -1)
		return (perror("dup2"), clear_all_exit(data, EXIT_FAILURE));
	close(data->hermes);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (perror("dup2"), clear_all_exit(data, EXIT_FAILURE));
	close(fd[1]);
	cmd_exe(data);
}
