/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:20 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/07 00:46:21 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// open, close, read, write,
// malloc, free, perror, access
// strerror, env, dup, dup2
// execve, exit, fork, pipe,
// unlink, wait, waitpid
int main(int ac, char **av, char **env)
{
	int		i;
	t_data	data;

	i = 2;
	setup(&data, ac, av, env);
	seek_and_execute(&data);
	return (0);
}
