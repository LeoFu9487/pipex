/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 02:21:00 by yfu               #+#    #+#             */
/*   Updated: 2021/05/27 23:36:05 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** If error -> exit
** return value :
** < >		0
** < >>		1
** << >		2
** << >>	3
*/

void	run_command(char *line, char **env)
{
	int		ct;
	char	*path;
	char	**args;
	int		idx;

	ct = -1;
	while (line[++ct])
		if (ft_isspace(line[ct]))
			line[ct] = ' ';
	args = ft_split(line, ' ');
	if (ft_strchr(args[0], '/'))
	{
		execve(args[0], args, env);
		ft_putstr_fd("pipex: ", 2);
		perror(args[0]);
		return ;//or exit ?
	}
	else
	{
		ct = -1;
		while (env[++ct])
		{
			if (ft_strncmp(env[ct], "PATH=", 5) == 0)
				break ;
		}
		if (!env[ct])
		{
			execve(args[0], args, env);
			ft_putstr_fd("pipex: ", 2);
			perror(args[0]);
			return ;//or exit ?
		}
	}
	env[ct] += 5;
	path = ft_calloc(ft_strlen(env[ct]) + 1 + ft_strlen(args[0]), sizeof(char));
	idx = 0;
	while (env[ct][0])
	{
		if (env[ct][0] == ':')
		{
			path[idx++] = '/';
			path[idx] = 0;
			ft_strcat(path, args[0]);
			execve(path, args, env);
			idx = 0;
		}
		else
		{
			path[idx++] = env[ct][0];
			path[idx] = 0;
			if (env[ct][1] == 0)
			{
				path[idx++] = '/';
				path[idx] = 0;
				ft_strcat(path, args[0]);
				execve(path, args, env);
			}
		}
		++env[ct];
	}
	ft_putstr_fd(args[0], 2);
	ft_putendl_fd(": command not found", 2);
}

int main(int ac, char **av, char **env)
{
	int		pipefd[2];
	int		status;
	int		fd;
	pid_t	pid;

	if (ac != 5)
		error_exit("arguments amount", 127);
	if (pipe(pipefd) < 0)
		error_exit("pipe create error", 127);
	pid = fork();
	if (pid == 0)/*child process : write into pipe*/
	{
		close(pipefd[0]);
		fd = open(av[1], O_RDONLY);
		if (errno)
		{
			close(pipefd[1]);
			ft_putstr_fd("pipex: ", 2);
			perror(av[1]);
		}
		else
		{
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			dup2(fd, STDIN_FILENO);
			close(fd);
			run_command(av[2], env);
		}
	}
	else/*parent process : read from pipe*/
	{
		waitpid(pid, &status, 0);
		close(pipefd[1]);
		fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (errno)
		{
			close(pipefd[0]);
			ft_putstr_fd("pipex: ", 2);
			perror(av[4]);
		}
		else
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			run_command(av[3], env);
		}
	}
}

/*
** todo : exit (return value)
*/