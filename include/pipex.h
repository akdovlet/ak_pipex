/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:07:37 by akdovlet          #+#    #+#             */
/*   Updated: 2024/05/15 03:35:50 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

# define HARDPATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct	s_data
{
	pid_t	*ids;
	char	**path;
	char	**av;
	char	**env;
	char	**cmd;
	int		fd[2];
	int		first;
	int		last;
	int		ac;
	int		hermes;
	int		cmd_count;
	int		exit_code;
	int		here_doc;
}	t_data;

/******************************ak_pipe.c**************************************/

// Child function for every command except for the last one, executes cmd
void	child(int fd[2], t_data *data, int i);
// Will pipe and fork making every cmd communicate, calls child
void	ak_pipe(t_data *data, int i);

/******************************ak_pipeout.c***********************************/

// Child function for the last cmd
void	child_out(t_data *data);
// Will fork the last cmd and will redirect it to outfile
void	ak_pipeout(t_data *data, int i);

/******************************check_file.c***********************************/

// Checks for reading rights on a given file, opens it if ok
int		check_file(char *file);

/******************************dr_here.c**************************************/

//	Forgot about Dre
void	dr_dre(t_data *data, int *fd);
// 
void	dr_here(t_data *data);

/********************************env_access.c**********************************/
char	**parse_env(char **env);
bool	file_access(char *file, int check);

/********************************free_exit.c***********************************/
void	ft_free(char **str);
void	clear_all(t_data *data);
void	clear_exit(t_data *data, int exit_code);

/******************************px_split.c**************************************/

char	**px_split(char const *s, char c);

/******************************seek_and_execute.c*****************************/
void	cmd_exe(t_data *data);
void	find_exec(char *cmd, t_data *data);
void	seek_and_execute(t_data	*data);

/******************************setup.c****************************************/
void	infile_setup(t_data *data, char **av);
bool	setup(t_data *data, int ac, char **av, char **env);
#endif
