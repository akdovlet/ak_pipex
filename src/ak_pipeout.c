/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ak_pipeout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 03:05:49 by akdovlet          #+#    #+#             */
/*   Updated: 2024/06/19 11:45:10 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// wifsignaled
// wtermsig
void	ak_pipeout(t_data *data, int i)
{
	int	status;
	int	j;

	j = 0;
	status = 0;
	data->pid_array[i] = fork();
	if (data->pid_array[i] < 0)
		return (perror("fork"), clear_all_exit(data, EXIT_FAILURE));
	if (data->pid_array[i] == CHILD)
		child_out(data);
	close(data->hermes);
	data->hermes = 0;
	while (j < data->cmd_count)
	{
		waitpid(data->pid_array[j], &status, 0);
		if (WIFSIGNALED(status))
		{
			data->exit_code = 128 + WTERMSIG(status);
			ft_dprintf(STDERR_FILENO, "Segmentation fault\n");
		}
		else
			data->exit_code = WEXITSTATUS(status);
		j++;
	}
}

void	child_out(t_data *data)
{
	open_outfile(data);
	if (data->outfile < 0)
		return (perror(data->outfile_name), clear_all_exit(data, EXIT_FAILURE));
	if (dup2(data->hermes, STDIN_FILENO) == -1)
		clear_all_exit(data, EXIT_FAILURE);
	close(data->hermes);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		clear_all_exit(data, EXIT_FAILURE);
	close(data->outfile);
	cmd_exe(data);
}
