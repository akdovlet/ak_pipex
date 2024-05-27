/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:41:38 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/27 10:40:05 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup(t_data *data, int ac, char **av, char **env)
{
	*data = (t_data){0};
	data->env = env;
	data->path = get_path_from_env(env);
	if (!data->path)
		return (perror("malloc"), exit(1));
	if (!ft_strcmp("here_doc", av[1]))
		data->here_doc_delimiter = av[2];
	else
		infile_setup(data, av);
	data->outfile_name = av[ac - 1];
	av[ac - 1] = NULL;
	data->commands = &av[2 + (data->here_doc_delimiter != NULL)];
	data->cmd_count = ac - (3 + (data->here_doc_delimiter != NULL));
}
