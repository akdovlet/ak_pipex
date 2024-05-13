/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:41:38 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/13 23:27:42 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	setup(t_data *data, int ac, char **av, char **env)
{
	data->path = parse_env(env);
	if (!data->path)
	{
		perror("pipex");
		return (false);
	}
	if (!ft_strcmp(av[1], "here_doc"))
		data->here_doc = true;
	else
		data->here_doc = false;
	data->first = check_file(av[1]);
	if (data->first == -1)
	{
		data->hermes = open("/dev/null", O_RDONLY);
		if (data->hermes < 0)
			return (perror(av[1]), false);
	}
	else
		data->hermes = data->first;
	data->exit_code = 0;
	data->cmd_count = 0;
	data->last = 0;
	data->cmd = NULL;
	data->ac = ac;
	data->av = av;
	data->env = env;
	return (true);
}
