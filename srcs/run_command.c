/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:35:31 by yfu               #+#    #+#             */
/*   Updated: 2021/05/28 16:37:51 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run_path(char *path, char **args, char **env)
{
	execve(path, args, env);
	ft_putstr_fd("pipex: ", 2);
	perror(args[0]);
	if (errno == 13)
		normal_exit(126);
	normal_exit(127);
}

static void	multiple_path(char *path, int ct[3], char **args, char **env)
{
	path[ct[1]++] = '/';
	path[ct[1]] = 0;
	ft_strcat(path, args[0]);
	execve(path, args, env);
	if (errno == 13)
		ct[2] = 1;
	ct[1] = 0;
}

static void	find_path(int ct[3], char **args, char **env)
{
	char	*path;

	env[ct[0]] += 5;
	path = ft_calloc(ft_strlen(env[ct[0]]) + 1
			+ ft_strlen(args[0]), sizeof(char));
	ct[1] = 0;
	while (env[ct[0]][0])
	{
		if (env[ct[0]][0] != ':')
		{
			path[ct[1]++] = env[ct[0]][0];
			path[ct[1]] = 0;
		}
		if (env[ct[0]][0] == ':' || env[ct[0]][1] == 0)
			multiple_path(path, ct, args, env);
		++env[ct[0]];
	}
	ft_putstr_fd(args[0], 2);
	if (ct[2])
		ft_putendl_fd(": permission denied", 2);
	ft_putendl_fd(": command not found", 2);
	normal_exit(127 - ct[2]);
}

void	run_command(char *line, char **env)
{
	int		ct[3];
	char	**args;

	ct[0] = -1;
	ct[2] = 0;
	while (line[++ct[0]])
		if (ft_isspace(line[ct[0]]))
			line[ct[0]] = ' ';
	args = ft_split(line, ' ');
	ct[0] = 0;
	if (ft_strchr(args[0], '/'))
		run_path(args[0], args, env);
	while (env[ct[0]] && ft_strncmp(env[ct[0]], "PATH=", 5))
		++ct[0];
	if (!env[ct[0]])
		run_path(args[0], args, env);
	find_path(ct, args, env);
}
