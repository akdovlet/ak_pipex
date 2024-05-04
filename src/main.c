/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:20 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/04 14:57:00 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

// open, close, read, write,
// malloc, free, perror, access
// strerror, env, dup, dup2
// execve, exit, fork, pipe,
// unlink, wait, waitpid

int	check_file(char *file)
{
	int	fd;

	if (!file_access(file, R_OK))
		return (perror("pipex3"), -1);
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			return (perror("pipex4"), -1);
	}
	return (fd);
}

int	mario_gaming(char *path, char *flags, char **env, int prevpipe)
{
	int	fd[2];
	int	id;

	pipe(fd);
	id = fork();
	if (!id)
	{
		close(fd[0]);
		printf("fd[1] is: %d\n", fd[1]);
		printf("prevpipe is: %d\n", prevpipe);
		if(dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror("pipex1"), close(fd[1]), -1);
		if (dup2(prevpipe, STDIN_FILENO) == -1)
			return (perror("pipex2"), close(prevpipe), -1);
		close(prevpipe);
		execve(path, &flags, env);
	}
	close(fd[1]);
	prevpipe = fd[0];
	return (prevpipe);
}

int	get_out(char *path, char *flags, char **env, int prevpipe)
{
	int	id;
	int	outfile;

	id = fork();
	outfile = open("test.txt", O_CREAT);
	if (!id)
	{
		dup2(prevpipe, STDIN_FILENO);
		close(prevpipe);
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		execve(path, &flags, env);
	}
	close(outfile);
	close(prevpipe);
	wait(NULL);
	return (0);
}

int main(int ac, char **av, char **env)
{
	int		i;
	int		id;
	int		fd[2];
	int		prev_pipe;

	i = 1;
	prev_pipe = check_file(av[i]);
	i++;
	if (prev_pipe < 0)
		return (1);
	while (i < ac)
	{
		prev_pipe = mario_gaming(av[i], av[i + 1], env, prev_pipe);
		i+= 2;
	}
	get_out(av[i], av[i], env, prev_pipe);
	return (0);
}
