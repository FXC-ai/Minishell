/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:36:30 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/22 14:49:23 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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

int	process_redirection(char *str)
{
	int in_fd = STDIN_FILENO;
	int out_fd = STDOUT_FILENO;
	char	**parsed_args;

	parsed_args = ft_split_lexer(str, ' ');
	/*printf("args[0] %s\n", parsed_args[0]);
	printf("args[1] %s\n", parsed_args[1]);
	printf("args[2] %s\n", parsed_args[2]);
	printf("args[3] %s\n", parsed_args[3]);*/
    char **current_command = parsed_args;
    while (*parsed_args)
	{
        if (strcmp(*parsed_args, ">") == 0)
		{
            *parsed_args = NULL;
            out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (out_fd == -1) {
                perror("open");
                exit(1);
            }
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
    //printf("Out fd %d\n", out_fd);
	return (out_fd);
}
