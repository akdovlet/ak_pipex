/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 00:41:28 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/19 19:14:45 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_all(t_data *data)
{
	ft_free(data->path);
	ft_free(data->cmd);
	free(data->pid_array);
	data->pid_array = NULL;
	if (data->infile > 0)
		close(data->infile);
	data->infile = 0;
	if (data->hermes > 0)
		close(data->hermes);
	data->hermes = 0;
	if (data->outfile > 0)
		close(data->outfile);
}

void	clear_exit(t_data *data, int exit_code)
{
	clear_all(data);
	exit(exit_code);
}
