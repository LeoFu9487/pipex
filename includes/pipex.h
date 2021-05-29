/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 02:21:03 by yfu               #+#    #+#             */
/*   Updated: 2021/05/29 01:51:48 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

/*
** Allowed functions :
** open
** close
** read
** write
** malloc
** waitpid
** wait
** free
** pipe
** dup2
** execve
** fork
** perror
** strerror
** exit
*/

void	message_exit(char *str, int exit_code);
void	normal_exit(int exit_code);
void	run_command(char *line, char **env);
void	bonus(int ac, char **av, char **env);
void	child_process(int pipefd, char **av, char **env);
void	parent_process(int pipefd, char **av, char **env);

#endif