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
#include <sys/stat.h>

//<-----------SIGNAL.C--------------->

void    signal_handler();
char	**lexer(char *str);
char	**ft_split_lexer(char const *s);
#endif