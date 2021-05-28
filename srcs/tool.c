/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 02:21:09 by yfu               #+#    #+#             */
/*   Updated: 2021/05/28 16:37:04 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	message_exit(char *str, int exit_code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putendl_fd(str, 2);
	ft_free_all();
	exit(exit_code);
}

void	normal_exit(int exit_code)
{
	ft_free_all();
	exit(exit_code);
}
