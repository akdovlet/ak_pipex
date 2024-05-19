/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:37 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/19 19:23:08 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

# define HARDPATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define ERR_MSG "pipex: %s: %s\n"
# define ERR_CMD "pipex: %s: command not found\n"
# define ERR_ARG "Error: Invalid number of arguments\n"
# define STDERR 2
# define CHILD 0

typedef struct s_data
{
	pid_t	*pid_array;
	char	**path;
	char	**env;
	char	**cmd;
	char	**commands;
	char	*here_doc_delimiter;
	char	*outfile_name;
	int		cmd_count;
	int		infile;
	int		outfile;
	int		hermes;
	int		exit_code;
}	t_data;

/******************************ak_pipe.c**************************************/
//	Will pipe and fork making every cmd communicate, calls child
void	ak_pipe(t_data *data, int i);
//	Child function for every command except for the last one, executes cmd
void	child(int fd[2], t_data *data);

/******************************ak_pipeout.c***********************************/
//	Child function for the last cmd
void	child_out(t_data *data);
//	Will fork the last cmd and will redirect it to outfile
void	ak_pipeout(t_data *data, int i);

/******************************cmd_exe.c**************************************/
//	Will execute the command and return the correct exit code
void	cmd_exe(t_data *data);

/******************************dr_here.c**************************************/
//	Creates a pipe and forks, calls dr_dre which reads 
//	from stdin and writes to pipe. Only called when here_doc_delimiter is set
void	dr_here(t_data *data);
//	Forgot about Dre
void	dr_dre(t_data *data, int *fd);
bool	delimiter_cmp(char *s1, char *s2);

/********************************env_access.c**********************************/
//	Will check if env is empty, if so will return 
//	a hard-coded path. If env exits will return the path from the env.
//	Otherwise returns the current dir
char	**get_path_from_env(char **env);
//	Will check if file has the correct permissions, simply calls access
bool	file_access(char *file, int check);

/******************************open_infile.c***********************************/
void	infile_setup(t_data *data, char **av);
int		infile_check(char *file);

/*****************************open_outfile.c***********************************/
void	open_outfile(t_data *data);

/********************************free_exit.c***********************************/
//	Frees everything
void	clear_all(t_data *data);
//	Calls clear_all and exits with the right exit code
void	clear_exit(t_data *data, int exit_code);

/******************************px_split.c**************************************/
// ft_split with a twist: adds '/' add the end of each word
char	**px_split(char const *s, char c);

/******************************seek_and_execute.c*****************************/
//	Driver code, will try and execute each command and make them communicate
void	seek_and_execute(t_data	*data);

/******************************setup.c****************************************/
/*	Does a lot of the heavy lifing, this isn't some silly parsing 
	or preemptive error check. 
	Instead, like the name implies, it sets all the variables to their right
	values. This function allows me to not have to change my driver 
	code regardless of how many commands I have to run 
	or if "here_doc" is given*/
void	setup(t_data *data, int ac, char **av, char **env);

#endif
