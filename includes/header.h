#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <termios.h>

typedef struct s_data
{
	int	nb_instuction;
	int	last_fd;
}   t_data;

typedef struct pipe
{
	char	**cmd1;
	char	**cmd2;
	int		fdin;
	int		fdout;
}	t_pipe;

typedef struct s_redirect
{
	char	*left_str;
	char	*right_str;
}	t_redirect;

void	wait_for_input();

//REDIRECTION.C
void	execute_command(char **parsed_args, int in_fd, int out_fd);
int 	process_redirection(char *str);

//SIGNAL.C

void    signal_handler();

//PARSE_ARGS.C

void    parsing(char **args);

//LEXER.C
char	**lexer(char *str);
char	**ft_split_lexer(char const *str, char c);
int		count_chr(const char *str, char c);

//UTILS.C
char *extract_command_name(const char *full_path);
#endif