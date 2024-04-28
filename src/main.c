/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:20 by akdovlet          #+#    #+#             */
/*   Updated: 2024/04/28 21:13:46 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

// open, close, read, write,
// malloc, free, perror, access
// strerror, env, dup, dup2
// execve, exit, fork, pipe,
// unlink, wait, waitpid
int main(int ac, char **av, char **env)
{
	int		i;
	int		id;
	t_data	data;
	int		fd[2];
	char	*strs[3];
	strs[0] = "/usr/bin/ls -la";
	strs[1] = "-la";
	strs[2] = NULL;
	char *str = "/usr/bin/ls -la";
	i = 1;
	id = fork();
	if (id == -1)
		return (1);
	if (pipe(fd) == -1)
		return (perror("pipex"), 1);
	if (!id)
	{
		execve("/usr/bin/ls", strs, env);
		perror("pipex");
	}
	return (0);
}
