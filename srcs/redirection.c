/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:05:42 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 16:55:34 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	execute_command(char **parsed_args, int in_fd, int out_fd)
{
	char	*cmd;


	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (execute_builtins(parsed_args) == 0)
	{
		if (parsed_args[0] == NULL)
			exit(0);
		cmd = normalize_cmd(parsed_args[0]);
		if (cmd == NULL)
			print_command_not_found(parsed_args[0]);
		execve(normalize_cmd(parsed_args[0]), parsed_args, g_env.env);
		perror(parsed_args[0]);
		exit(errno);
	}
}

int	process_delimiter(char *del)
{
	char	buffer[1024];
	ssize_t	rdd;
	int		fd;
	char	*del_n;

	del_n = ft_strjoin(del, "\n");
	fd = open("TMPDOC", O_TRUNC | O_CREAT | O_WRONLY, 0777);
	rdd = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	while (rdd > 0)
	{
		buffer[rdd] = '\0';
		if (ft_strcmp(del_n, buffer) == 0)
			break ;
		write(fd, buffer, rdd);
		rdd = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	}
	close(fd);
	fd = open("TMPDOC", O_RDONLY);
	unlink("TMPDOC");
	free(del_n);
	return (fd);
}

int	process_redirection(char **redirections, int **in_out_fd)
{
	char	*redirection;

	(*in_out_fd)[0] = STDIN_FILENO;
	(*in_out_fd)[1] = STDOUT_FILENO;
	while (*redirections)
	{
		redirection = *redirections++;
		if (ft_strncmp(redirection, ">>", 2) == 0)
		{
			if (process_double_right_r(&redirection, in_out_fd) == 0)
				return (-1);
		}
		else if (ft_strncmp(redirection, ">", 1) == 0)
		{
			if (process_single_right_r(&redirection, in_out_fd) == 0)
				return (-1);
		}
		else if (ft_strncmp(redirection, "<<", 2) == 0)
		{
			if (process_double_left_r(&redirection, in_out_fd) == 0)
				return (-1);
		}
		else if (ft_strncmp(redirection, "<", 1) == 0)
			if (process_single_left_r(&redirection, in_out_fd) == 0)
				return (-1);
	}
	return (1);
}
