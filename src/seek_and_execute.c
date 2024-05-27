/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_and_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:52:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/27 10:36:26 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	seek_and_execute(t_data	*data)
{
	int	i;

	i = 0;
	data->pid_array = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pid_array)
		return (clear_all_exit(data, EXIT_FAILURE));
	ft_memset(data->pid_array, 0, sizeof(pid_t) * data->cmd_count);
	if (data->here_doc_delimiter)
		dr_here(data);
	while (i < data->cmd_count - 1)
	{
		data->cmd = ft_multi_split(data->commands[i], " '");
		if (!data->cmd)
			return (clear_all_exit(data, EXIT_FAILURE));
		ak_pipe(data, i);
		ft_free(data->cmd);
		i++;
	}
	data->cmd = ft_multi_split(data->commands[i], " '");
	if (!data->cmd)
		return (clear_all_exit(data, EXIT_FAILURE));
	ak_pipeout(data, i);
}
