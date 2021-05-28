/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 02:21:00 by yfu               #+#    #+#             */
/*   Updated: 2021/05/28 16:37:31 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(int pipefd[2], char **av, char **env)
{
	int	fd;

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

static void	parent_process(int pipefd[2], char **av, char **env)
{
	int	fd;

	wait(NULL);
	close(pipefd[1]);
	fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (errno)
	{
		close(pipefd[0]);
		ft_putstr_fd("pipex: ", 2);
		perror(av[4]);
		normal_exit(1);
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

int	main(int ac, char **av, char **env)
{
	int		pipefd[2];

	if (ac != 5)
		message_exit("arguments amount", 2);
	if (pipe(pipefd) < 0)
		message_exit("pipe create error", 1);
	if (fork() == 0)
		child_process(pipefd, av, env);
	else
		parent_process(pipefd, av, env);
	return (0);
}
