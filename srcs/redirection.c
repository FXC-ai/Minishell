/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:31:55 by fcoindre          #+#    #+#             */
/*   Updated: 2023/03/30 11:19:28 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/header.h"


void execute_command(char **parsed_args, int in_fd, int out_fd, char *env[])
{
    int r;

    pid_t child_pid = fork();
    if (child_pid == 0)
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

        r = is_builtins(*parsed_args);
        if (r == 1)
            echo_process(parsed_args);
        else if (r == 2)
            cd_process(parsed_args);
        else if (r == 3)
            pwd_process(parsed_args);
        else if (r == 4)
            export_process(parsed_args, env);
        else if (r == 5)
            export_process(parsed_args, env);
        else if (r == 6)
            export_process(parsed_args, env);
        else if (r == 7)
            exit_process();
        else
        {
            execve(normalize_cmd(parsed_args[0], env), parsed_args, env);
            perror(parsed_args[0]);
            exit(0);
        }
        exit(0);
    }
    else
    {
        waitpid(child_pid, NULL, 0);
    }
}


void	execute_command_2(char **parsed_args, int in_fd, int out_fd, char *env[])
{
	int	r;

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
	if (r == 1)
		echo_process(parsed_args);
	else if (r == 2)
		cd_process(parsed_args);
	else if (r == 3)
		pwd_process(parsed_args);
	else if (r == 4)
		export_process(parsed_args, env);
	else if (r == 5)
		export_process(parsed_args, env);
	else if (r == 6)
		export_process(parsed_args, env);
	else if (r == 7)
		exit_process();
	else
	{
		execve(normalize_cmd(parsed_args[0], env), parsed_args, env);
		perror(parsed_args[0]);
		exit(1);
	}
		
}

static int process_delimiter(char *del)
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
        buffer[rdd] = '\0';
		//printf("OK\n");
        if (ft_strcmp(del_n, buffer) == 0)
        {
			//printf("OK!\n");
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
    int in_fd = STDIN_FILENO;
    int out_fd = STDOUT_FILENO;
    char **parsed_args;
    parsed_args = ft_split_lexer(str, ' ');
	
    char **current_command = parsed_args;
	//print_tab(current_command);
    while (*parsed_args)
    {
		//printf("%s\n", *parsed_args);
        if (ft_strcmp(*parsed_args, ">") == 0)
        {
            *parsed_args = NULL;
            out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (in_fd == -1)
			{
				perror("open");
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
				perror("open");
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
				perror("open");
				return -1;
			}
            parsed_args++;
        }
        else if (ft_strcmp(*parsed_args, "<<") == 0)
        {
			//print_tab(parsed_args);
			print_tab((current_command));
            *parsed_args = NULL;
			print_tab((current_command));

            in_fd = process_delimiter(*(parsed_args + 1));
			//current_command++;
			//printf("LINE %s\n", *(parsed_args + 1));
            parsed_args += 2;
			current_command += 2;
        }
        else
        {
            parsed_args++;
        }
    }
	
	//print_tab(current_command);
	if (mode)
		execute_command(current_command, in_fd, out_fd, env);
	else
	    execute_command_2(current_command, in_fd, out_fd, env);
	
    	
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