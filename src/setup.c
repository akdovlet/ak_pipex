/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:41:38 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/07 02:17:22 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup(t_data *data, int ac, char **av, char **env)
{
	data->path = parse_env(env);
	data->first = check_file(av[1]);
	if (data->first == -1)
	{
		data->hermes = open("/dev/null", O_RDONLY);
		if (data->hermes < 0)
			perror("pipex");
	}
	else
		data->hermes = data->first;
	data->last = 0;
	data->cmd = NULL;
	data->ac = ac;
	data->av = av;
	data->env = env;
}
