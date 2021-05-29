/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 22:57:30 by yfu               #+#    #+#             */
/*   Updated: 2021/05/29 02:27:45 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	here_document(int fd, char *eof)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) != 0)
			ft_putendl_fd(line, fd);
		else
			normal_exit(0);
	}
	if (ft_strncmp(line, eof, ft_strlen(eof) + 1) != 0)
	{
		ft_putstr_fd(line, fd);
		ft_putstr_fd("pipex: warning: here-document delimited", 2);
		ft_putstr_fd(" by end-of-file (wanted `", 2);
		ft_putstr_fd(eof, 2);
		ft_putendl_fd("\')", 2);
	}
	normal_exit(0);
}

static void	recursive(int now, int fd, char **av, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (now == 2 && ft_strncmp(av[1], "<<", 3) == 0)
		here_document(fd, av[2]);
	if (now == 2)
		child_process(fd, av, env);
	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		run_command(av[now], env);
	}
	else
	{
		close(pipefd[0]);
		recursive(now - 1, pipefd[1], av, env);
	}
}

static void	sub(int ac, char **av, char **env, int pipefd[2])
{
	int	fd;

	close(pipefd[1]);
	if (ft_strncmp(av[ac - 1], ">>", 3) == 0)
		fd = open(av[--ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0664);
	else
		fd = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (errno)
	{
		close(pipefd[0]);
		ft_putstr_fd("pipex: ", 2);
		perror(av[ac - 1]);
		normal_exit(1);
	}
	else
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		run_command(av[ac - 2], env);
	}
}

void	bonus(int ac, char **av, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		message_exit("pipe create error", 1);
	pid = fork();
	if (pid)
	{
		waitpid(pid, NULL, 0);
		sub(ac, av, env, pipefd);
	}
	else
	{
		close(pipefd[0]);
		if (ft_strncmp(av[ac - 1], ">>", 3) == 0)
			recursive(ac - 4, pipefd[1], av, env);
		else
			recursive(ac - 3, pipefd[1], av, env);
	}
}
