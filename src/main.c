/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:20 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/17 18:00:42 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	print_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		ft_printf("%s\n", env[i]);
// 		i++;
// 	}
// }

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac < 5)
	{
		ft_dprintf(STDERR_FILENO, "Error: Invalid number of arguments\n");
		return (1);
	}
	// print_env(env);
	if (!setup(&data, ac, av, env))
		return (1);
	seek_and_execute(&data);
	clear_all(&data);
	return (data.exit_code);
}
