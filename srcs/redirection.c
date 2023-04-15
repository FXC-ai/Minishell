/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:05:42 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/15 12:21:58 by fcoindre         ###   ########.fr       */
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
		perror(parsed_args[0]);
		exit(errno);
	}
	//exit(0);
}

int process_delimiter(char *del)
{
	char buffer[1024];
	ssize_t rdd;
	int fd;
	char *del_n = ft_strjoin(del, "\n");

	//ree(del);
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

int		process_redirection(char **redirections, int **in_out_fd, char *env[])
{
	(void) env;
	char **current_command;

	(*in_out_fd)[0] = STDIN_FILENO;
	(*in_out_fd)[1] = STDOUT_FILENO;
	

	//printf("Before process_redirection : in_in_out_fd[1][0] = %d / in_out_fd[1] = %d\n", in_in_out_fd[1][0], in_out_fd[1]);

	//printf("str = %s\n", str);


	//print_tab(parsed_args);
	current_command = redirections;
	while (*redirections)
	{
		//printf("*redirection = %s\n", *redirections);

		if (ft_strncmp(*redirections, ">>", 2) == 0)
		{
			(*redirections)++;
			(*redirections)++;
			while (is_space(**redirections))
			{
				(*redirections)++;
			}

			(*in_out_fd)[1] = open(*(redirections), O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if ((*in_out_fd)[1] == -1)
			{
				perror(*(redirections));
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

			(*in_out_fd)[0] = open(*(redirections), O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if ((*in_out_fd)[0] == -1)
			{
				perror(*(redirections));
				return -1;
			}
		}
		
		/*
		else if (ft_strcmp(*redirections, "<") == 0)
		{
			*redirections = NULL;
			in_out_fd[0] = open(*(redirections + 1), O_RDONLY);
			
			if (in_out_fd[0] == -1)
			{
				perror(*(redirections + 1));
				return -1;
			}
			redirections++;
		}
		else if (ft_strncmp(*redirections, "<<", 2) == 0)
		{
			*redirections = NULL;

			in_out_fd[0] = process_delimiter(*(redirections + 1));
			if (in_out_fd[0] == -1)
			{
				return (-1);
			}
			//print_tab(redirections + 2);
			//print_tab(current_command);
			redirections += 2;

		}*/

		redirections++;

	}
	
	/*
	if (*current_command)
	{
		execute_command(current_command, in_out_fd[0], out_fd, env);	
	}
	else
	{
		perror("cmd");
	}
	*/
	//printf("After process_redirection : in_out_fd[0] = %d / out_fd = %d\n", in_out_fd[0], out_fd);

	/*if (in_out_fd[0] != STDIN_FILENO)
	{
		close(in_out_fd[0]);
	}
	if (in_out_fd[1] != STDOUT_FILENO)
	{
		close(in_out_fd[1]);
	}*/
	return (1);
}