/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ak_pipeout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 03:05:49 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/18 23:13:37 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_out(t_data *data)
{
	if (dup2(data->hermes, STDIN_FILENO) == -1)
		clear_exit(data, EXIT_FAILURE);
	close(data->hermes);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		clear_exit(data, EXIT_FAILURE);
	close(data->outfile);
	cmd_exe(data);
}

void	open_outfile(t_data *data)
{
	if (data->here_doc_delimiter)
		data->outfile = open(data->outfile_name, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->outfile = open(data->outfile_name, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ak_pipeout(t_data *data, int i)
{
	int	status;
	int	j;

	j = 0;
	status = 0;
	open_outfile(data);
	if (data->outfile < 0)
		return (perror(data->outfile_name), clear_exit(data, EXIT_FAILURE));
	data->ids[i] = fork();
	if (data->ids[i] < 0)
		return (perror("fork"), clear_exit(data, EXIT_FAILURE));
	if (data->ids[i] == CHILD)
		child_out(data);
	close(data->hermes);
	data->hermes = 0;
	while (j < data->cmd_count)
	{
		waitpid(data->ids[j], &status, 0);
		data->exit_code = WEXITSTATUS(status);
		j++;
	}
}
