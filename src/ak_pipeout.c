/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ak_pipeout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 03:05:49 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/17 10:22:50 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_out(t_data *data)
{
	if (dup2(data->hermes, STDIN_FILENO) == -1)
		clear_exit(data, EXIT_FAILURE);
	close(data->hermes);
	if (dup2(data->last, STDOUT_FILENO) == -1)
		clear_exit(data, EXIT_FAILURE);
	close(data->last);
	cmd_exe(data);
}

void	open_outfile(t_data *data)
{
	if (data->here_doc)
		data->last = open(data->av[data->ac - 1], \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->last = open(data->av[data->ac - 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ak_pipeout(t_data *data, int i)
{
	int	status;
	int	j;

	j = 0;
	status = 0;
	open_outfile(data);
	if (data->last < 0)
		return (perror(data->av[data->ac -1]), clear_exit(data, EXIT_FAILURE));
	data->ids[i - (2 + data->here_doc)] = fork();
	if (data->ids[i - (2 + data->here_doc)] < 0)
		return (perror("pipex"), clear_exit(data, EXIT_FAILURE));
	if (!data->ids[i - (2 + data->here_doc)])
		child_out(data);
	close(data->hermes);
	data->hermes = 0;
	while (j < data->ac - (3 + data->here_doc))
	{
		waitpid(data->ids[j], &status, 0);
		data->exit_code = WEXITSTATUS(status);
		j++;
	}
}
