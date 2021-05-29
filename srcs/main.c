/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 02:21:00 by yfu               #+#    #+#             */
/*   Updated: 2021/05/29 02:00:35 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int pipefd, char **av, char **env)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (errno)
	{
		close(pipefd);
		ft_putstr_fd("pipex: ", 2);
		perror(av[1]);
		normal_exit(1);
	}
	else
	{
		dup2(pipefd, STDOUT_FILENO);
		close(pipefd);
		dup2(fd, STDIN_FILENO);
		close(fd);
		run_command(av[2], env);
	}
}

void	parent_process(int pipefd, char **av, char **env)
{
	int	fd;

	wait(NULL);
	fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (errno)
	{
		close(pipefd);
		ft_putstr_fd("pipex: ", 2);
		perror(av[4]);
		normal_exit(1);
	}
	else
	{
		dup2(pipefd, STDIN_FILENO);
		close(pipefd);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		run_command(av[3], env);
	}
}

#ifdef BONUS
int	main(int ac, char **av, char **env)
{
	int	ac_min;

	ac_min = 5;
	if (ac < ac_min)
		message_exit("arguments amount", 2);
	if (ft_strncmp(av[1], "<<", 3) == 0)
		++ac_min;
	if (ft_strncmp(av[ac - 1], ">>", 3) == 0)
		++ac_min;
	if (ac < ac_min)
		message_exit("argument amount", 2);
	bonus(ac, av, env);
}

#else
int	main(int ac, char **av, char **env)
{
	int		pipefd[2];

	if (ac != 5)
		message_exit("arguments amount", 2);
	if (pipe(pipefd) < 0)
		message_exit("pipe create error", 1);
	if (fork() == 0)
	{
		close(pipefd[0]);
		child_process(pipefd[1], av, env);
	}
	else
	{
		close(pipefd[1]);
		parent_process(pipefd[0], av, env);
	}
	return (0);
}
#endif