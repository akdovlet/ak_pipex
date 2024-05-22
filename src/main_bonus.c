/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:44:42 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/22 16:52:47 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac < 5)
	{
		ft_dprintf(STDERR, ERR_ARG);
		return (1);
	}
	setup(&data, ac, av, env);
	seek_and_execute(&data);
	clear_all(&data);
	return (data.exit_code);
}
