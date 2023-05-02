/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:35:06 by vgiordan          #+#    #+#             */
/*   Updated: 2023/05/02 14:56:39 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	process_double_right_r(char **redirection, int **in_out_fd)
{
	(*redirection) += 2;
	while (is_space(**redirection))
		(*redirection)++;
	(*in_out_fd)[1] = open(*redirection, O_WRONLY | O_CREAT |  O_APPEND, 0644);
	if ((*in_out_fd)[1] == -1)
	{
		perror(*redirection);
		g_env.ms_errno = 1;
		return (0);
	}
	return (1);
}

int	process_double_left_r(char **redirection, int **in_out_fd)
{
	(*redirection) += 2;
	while (is_space(**redirection))
		(*redirection)++;
	(*in_out_fd)[0] = process_delimiter(*redirection);
	if ((*in_out_fd)[0] == -1)
	{
		perror(*redirection);
		g_env.ms_errno = 1;
		return (0);
	}
	return (1);
}

int	process_single_right_r(char **redirection, int **in_out_fd)
{
	(*redirection)++;
	while (is_space(**redirection))
		(*redirection)++;
	(*in_out_fd)[1] = open(*redirection, O_WRONLY | O_CREAT |  O_TRUNC, 0644);
	if ((*in_out_fd)[1] == -1)
	{
		perror(*redirection);
		g_env.ms_errno = 1;
		return (0);
	}
	return (1);
}

int	process_single_left_r(char **redirection, int **in_out_fd)
{
	(*redirection)++;
	while (is_space(**redirection))
		(*redirection)++;
	(*in_out_fd)[0] = open(*redirection, O_RDONLY);
	if ((*in_out_fd)[0] == -1)
	{
		perror(*redirection);
		g_env.ms_errno = 1;
		return (0);
	}
	return (1);
}
