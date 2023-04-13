/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:31:55 by fcoindre          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/13 14:59:30 by fcoindre         ###   ########.fr       */
=======
/*   Updated: 2023/04/13 14:59:24 by vgiordan         ###   ########.fr       */
>>>>>>> 12b7b475de22138881fb587d0865bfb385e314b0
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	execute_command(char **parsed_args, int in_fd, int out_fd, char *env[])
{
	int		r;
	int		status;
	char	*cmd;
	
	r = is_builtins(*parsed_args);
	if (r == BUILTIN_CD)
		cd_process(parsed_args, env);
	else if (r == BUILTIN_EXPORT)
		export_process(parsed_args, env);
	else if (r == BUILTIN_UNSET)
		unset_process(parsed_args, env);
	else if (r == BUILTIN_EXIT)
		exit_process();

		
	global_sig.pid = fork();
	if (global_sig.pid == 0)
	{
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
		if (r == BUILTIN_ECHO)
			echo_process(parsed_args);
		else if (r == BUILTIN_PWD)
			pwd_process(parsed_args);
		else if (r == 6)
			env_process(parsed_args, env);
		else if (r == 7)
			exit_process();
		else if (r == 0)
		{
			cmd = normalize_cmd(parsed_args[0], env);
			if (cmd == NULL)
				print_command_not_found(parsed_args[0]);
			execve(cmd, parsed_args, env);
			
			//ms_errno = errno;
			//printf("redirection errno = %d ms_errno = %d\n", errno, ms_errno);
			perror(parsed_args[0]);
			exit(errno);
		}
		exit(0);
	}
	else
	{
		waitpid(global_sig.pid, &status, 0);
		//ft_putstr_fd("waitpid\n", 2);
		if (WIFEXITED(status))
		{
			global_sig.ms_errno = WEXITSTATUS(status);

		}
	}
}

void	execute_command_2(char **parsed_args, int in_fd, int out_fd, char *env[])
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

int process_redirection(char *str, char *env[], int mode)
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
		if (mode)
		{
<<<<<<< HEAD
			printf("avant execution de command 1\n");
			execute_command(current_command, in_fd, out_fd, env);
			printf("avant execution de command 2\n");
=======
			//printf("avant execution de command 1");
			execute_command(current_command, in_fd, out_fd, env);
			//printf("avant execution de command 2");
>>>>>>> 12b7b475de22138881fb587d0865bfb385e314b0

		}
		else
		{
			//printf("avant execution de command 2");

			execute_command_2(current_command, in_fd, out_fd, env);

			//printf("avant execution de command 1");

		}
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