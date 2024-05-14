/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:41:38 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/13 17:03:28 by akdovlet         ###   ########.fr       */
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
	data->first = check_file(av[1]);
	if (data->first == -1)
	{
		data->hermes = open("/dev/null", O_RDONLY);
		if (data->hermes < 0)
			return (perror(av[1]), ft_free(data->path), false);
	}
	else
		data->hermes = data->first;
	data->ids = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	data->last = 0;
	data->ac = ac;
	data->av = av;
	data->env = env;
	return (true);
}
