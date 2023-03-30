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
# include <termios.h>
# include <errno.h>

# define BUFFER_SIZE 1024

#define BUILTIN_ECHO 1
#define BUILTIN_CD 2
#define BUILTIN_PWD 3
#define BUILTIN_EXPORT 4
# define BUILTIN_UNSET 5
# define BUILTIN_ENV 6
#define BUILTIN_EXIT 7


void	rl_replace_line (const char *text, int clear_undo);

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

void	wait_for_input(char *env[]);

//REDIRECTION.C
void	execute_command(char **parsed_args, int in_fd, int out_fd, char *env[]);
int		process_redirection(char *str, char *env[], int mode);

//SIGNAL.C

void    signal_handler();

//PARSE_ARGS.C

void    parsing(char **args, char *env[]);

//LEXER.C
char	**lexer(char *str, char *env[]);
char	**ft_split_lexer(char const *str, char c);
int		count_chr(const char *str, char c);

char	**ft_lexer_no_quote(char const *str, char c);

//UTILS.C
char *extract_command_name(const char *full_path);
void	ft_free_tabs(char **tab, int h);
int	size_tab(char **tab);
char	**create_tab_paths(char *env[]);
char	*create_path_cmd(char *path, char *cmd);
char	*cmd_exists(char *cmd, char *env[]);
char	*normalize_cmd(char* str, char *env[]);
int		is_builtins(char *str);
void	print_tab(char **tab);


//MS_PIPE.C
void ms_pipe(char *tab_cmd[2], char *env[]);
void ms_pipe2(char **tab_cmds, char *env[]);
int ms_pipe3(int process_num, char **tab_cmds, char *env[]);

//BUILTINS
void	echo_process(char **cmd);
void	cd_process(char **current_command);
void	pwd_process();
int		unset_process(char **parsed_args, char *env[]);
void	env_process(char **parsed_args, char *env[]);
void	export_process(char **current_command, char *env[]);
void    exit_process();
int		unset_process_str(char *key, char *env[]);




#endif