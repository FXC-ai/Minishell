/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:05:42 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/15 18:26:19 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/header.h"


void	execute_command(char **parsed_args, int in_fd, int out_fd, char *env[])
{
	int		r;
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
	r = is_builtins(*parsed_args);

	if (r == BUILTIN_ECHO)
		echo_process(parsed_args);
	else if (r == BUILTIN_CD)
		cd_process(parsed_args, env);
	else if (r == BUILTIN_PWD)
		pwd_process(parsed_args);
	else if (r == BUILTIN_EXPORT)
		export_process(parsed_args, env);
	else if (r == BUILTIN_UNSET)
		unset_process(parsed_args, env);
	else if (r == BUILTIN_ENV)
		env_process(parsed_args, env);
	else if (r == BUILTIN_EXIT)
		exit_process();
	else
	{
		cmd = normalize_cmd(parsed_args[0], env);
		if (cmd == NULL)
			print_command_not_found(parsed_args[0]);
		execve(normalize_cmd(parsed_args[0], env), parsed_args, env);
	}

}

int process_delimiter(char *del)
{
	char buffer[1024];
	ssize_t rdd;
	int fd;
	char *del_n = ft_strjoin(del, "\n");

	fd = open("TMPDOC", O_TRUNC | O_CREAT | O_WRONLY, 0777);

	rdd = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	while (rdd > 0)
	{
		buffer[rdd] = '\0';
		if (ft_strcmp(buffer, "\4\n") == 0)
		{
			ft_putstr_fd("DEDANS\n", 2);
			close(fd);
			unlink("TMPDOC");
			return (-1);
		}
		if (ft_strcmp(del_n, buffer) == 0)
		{
			break;
		}
		write(fd, buffer, rdd);
		rdd = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	}
	close(fd);
	fd = open("TMPDOC", O_RDONLY);
	unlink("TMPDOC");
	return fd;
}

int		process_redirection(char **redirections, int **in_out_fd, char *env[])
{
	(void) env;
	char **current_command;

	(*in_out_fd)[0] = STDIN_FILENO;
	(*in_out_fd)[1] = STDOUT_FILENO;
	
	current_command = redirections;
	while (*redirections)
	{

		if (ft_strncmp(*redirections, ">>", 2) == 0)
		{
			(*redirections)++;
			(*redirections)++;
			while (is_space(**redirections))
			{
				(*redirections)++;
			}

			(*in_out_fd)[1] = open(*(redirections), O_WRONLY | O_CREAT | O_APPEND, 0777);
			if ((*in_out_fd)[1] == -1)
			{
				perror(*(redirections));
				global_sig.ms_errno = 1;
				return -1;
			}
		}
		else if (ft_strncmp(*redirections, ">", 1) == 0)
		{
			(*redirections)++;
			while (is_space(**redirections))
			{
				(*redirections)++;
			}

			(*in_out_fd)[1] = open(*(redirections), O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if ((*in_out_fd)[1] == -1)
			{
				perror(*(redirections));
				global_sig.ms_errno = 1;
				return -1;
			}
		}
		else if (ft_strncmp(*redirections, "<<", 2) == 0)
		{
			(*redirections)++;
			(*redirections)++;
			while (is_space(**redirections))
			{
				(*redirections)++;
			}

			(*in_out_fd)[0] = process_delimiter(*redirections);
			if ((*in_out_fd)[0] == -1)
			{
				perror(*(redirections));
				global_sig.ms_errno = 1;
				return -1;
			}
		}
		else if (ft_strncmp(*redirections, "<", 1) == 0)
		{
			(*redirections)++;
			while (is_space(**redirections))
			{
				(*redirections)++;
			}

			(*in_out_fd)[0] = open(*(redirections), O_RDONLY, 0777);
			if ((*in_out_fd)[0] == -1)
			{
				perror(*(redirections));
				global_sig.ms_errno = 1;
				return -1;
			}
		}
		
		redirections++;

	}
	
	return (1);
}