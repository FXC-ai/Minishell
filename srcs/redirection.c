/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:05:42 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/13 17:28:36 by vgiordan         ###   ########.fr       */
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
	else
	{
		cmd = normalize_cmd(parsed_args[0], env);
		if (cmd == NULL)
			print_command_not_found(parsed_args[0]);
		execve(normalize_cmd(parsed_args[0], env), parsed_args, env);
		perror(parsed_args[0]);
		exit(errno);
	}
	exit(0);
}

int process_delimiter(char *del)
{
	char buffer[1024];
	ssize_t rdd;
	int fd;
	char *del_n = ft_strjoin(del, "\n");

	free(del);
	fd = open("TMPDOC", O_TRUNC | O_CREAT | O_WRONLY, 0777);

	rdd = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	while (rdd > 0)
	{
	
		/*if (global_sig.sig_int == 1)
		{
			ft_putstr_fd("DEDANS\n", 2);
			close(fd);
			unlink("TMPDOC");
			global_sig.sig_int = 0;
			return (-1);
		}*/
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

int process_redirection(char *str, char *env[])
{
	int in_fd;
	int out_fd;
	char **parsed_args;
	char **current_command;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;

	//printf("Before process_redirection : in_fd = %d / out_fd = %d\n", in_fd, out_fd);

	//printf("str = %s\n", str);
	parsed_args = ft_split_lexer_no_quote(str, ' ');
	current_command = parsed_args;
	while (*parsed_args)
	{
		if (ft_strcmp(*parsed_args, ">") == 0)
		{
			*parsed_args = NULL;
			out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (in_fd == -1)
			{
				perror(*(parsed_args + 1));
				return -1;
			}
			parsed_args++;
		}
		else if (ft_strcmp(*parsed_args, ">>") == 0)
		{
			*parsed_args = NULL;
			out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (in_fd == -1)
			{
				perror(*(parsed_args + 1));
				return -1;
			}
			parsed_args++;
		}
		else if (ft_strcmp(*parsed_args, "<") == 0)
		{
			*parsed_args = NULL;
			in_fd = open(*(parsed_args + 1), O_RDONLY);
			
			if (in_fd == -1)
			{
				perror(*(parsed_args + 1));
				return -1;
			}
			parsed_args++;
		}
		else if (ft_strncmp(*parsed_args, "<<", 2) == 0)
		{
			*parsed_args = NULL;

			in_fd = process_delimiter(*(parsed_args + 1));
			if (in_fd == -1)
			{
				return (-1);
			}
			parsed_args += 2;
			current_command += 2;
		}
		else
		{
			parsed_args++;
		}
	}
	
	if (*current_command)
	{
		execute_command(current_command, in_fd, out_fd, env);	
	}
	else
	{
		perror("cmd");
	}
	
	//printf("After process_redirection : in_fd = %d / out_fd = %d\n", in_fd, out_fd);

	if (in_fd != STDIN_FILENO)
	{
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		close(out_fd);
	}
	return (out_fd);
}