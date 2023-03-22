/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:31:55 by fcoindre          #+#    #+#             */
/*   Updated: 2023/03/22 18:35:28 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/header.h"

static int delimiter_parse(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '<' && str[i + 1] == '<')
            return (1);
        i++;
    }
    return (0);
}

void	execute_command(char **parsed_args, int in_fd, int out_fd)
{
    if (fork() == 0)
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
        execvp(parsed_args[0], parsed_args);
        perror(parsed_args[0]);
        exit(1);
    }
}

static int process_delimiter(char *delimiter)
{
    int pipe_fd[2];
    char buffer[1024];
    (void ) delimiter;
    ssize_t num_read;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    while (1)
    {
        num_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        printf("Buffer %s\n", buffer);
        if (num_read <= 0)
        {
            break;
        }
    }
    close(pipe_fd[1]);
    return pipe_fd[0];
}

int	process_redirection(char *str)
{
	int in_fd = STDIN_FILENO;
	int out_fd = STDOUT_FILENO;
	char	**parsed_args;

	parsed_args = ft_split_lexer(str, ' ');
    char **current_command = parsed_args;
    while (*parsed_args)
	{
        if (strcmp(*parsed_args, ">") == 0)
		{
            *parsed_args = NULL;
            out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_TRUNC, 0777);

            if (out_fd == -1) {
                perror("open");
                exit(1);
            }
        }
        else if (strcmp(*parsed_args, ">>") == 0)
        {
            out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_APPEND, 0777);
        }
		else if (strcmp(*parsed_args, "<") == 0)
		{
            *parsed_args = NULL;
            in_fd = open(*(parsed_args + 1), O_RDONLY | O_CREAT);

            if (in_fd == -1)
			{
                perror("open");
                exit(1);
            }
        }
        else if (delimiter_parse(*parsed_args) == 0)
        {
            in_fd = process_delimiter(*(parsed_args + 1));
        }
        parsed_args++;
    }
    execute_command(current_command, in_fd, out_fd);

    if (in_fd != STDIN_FILENO)
	{
        close(in_fd);
    }
    if (out_fd != STDOUT_FILENO)
	{
        close(out_fd);
    }
    wait(NULL);
    wait(NULL);

	return (out_fd);
}
