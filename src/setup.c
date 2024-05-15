/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:41:38 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/15 03:15:19 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	infile_setup(t_data *data, char **av)
{
	data->here_doc = 0;
	data->first = check_file(av[1]);
	if (data->first == -1)
	{
		data->hermes = open("/dev/null", O_RDONLY);
		if (data->hermes < 0)
			return (perror(av[1]), ft_free(data->path), exit(EXIT_FAILURE));
	}
	else
		data->hermes = data->first;
}

bool	setup(t_data *data, int ac, char **av, char **env)
{
	data->path = parse_env(env);
	if (!data->path)
		return (perror("pipex"), false);
	if (!ft_strcmp("here_doc", av[1]))
		data->here_doc = 1;
	else
		infile_setup(data, av);
	data->ids = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	data->last = 0;
	data->ac = ac;
	data->av = av;
	data->env = env;
	return (true);
}
