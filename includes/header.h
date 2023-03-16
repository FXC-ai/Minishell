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

typedef struct s_data
{
	int	nb_instuction;
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


//REDIRECTION.C
int		string_has_right_redirection(char *str);
int		string_has_left_redirection(char *str);
t_pipe	manage_redirection(char *str);

//SIGNAL.C

void    signal_handler();

//PARSE_ARGS.C

void    parsing(char **args);

//LEXER.C
char	**lexer(char *str);
char	**ft_split_lexer(char const *str, char c);
int		count_chr(const char *str, char c);
#endif