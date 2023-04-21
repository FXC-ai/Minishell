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
# include <stdbool.h>

# define BUFFER_SIZE 1024

# define BUILTIN_ECHO 1
# define BUILTIN_CD 2
# define BUILTIN_PWD 3
# define BUILTIN_EXPORT 4
# define BUILTIN_UNSET 5
# define BUILTIN_ENV 6
# define BUILTIN_EXIT 7

# define NO_SUCH_FILE_DIRECTORY 1
# define COMMAND_NOT_FOUND 127
# define SUCCESS 0
# define PERMISSION_DENIED 1

typedef struct	s_sig
{
	int 	sig_int;
	int		sig_quit;
	int		ms_errno;
	int		program_in_process;
	pid_t	pid;
	char	**env;

} t_sig;

typedef struct s_utils
{
	int		i;
	int		j;
	int		start;
	int		in_quote;
	char	quote;
	int		in_word;
	int		count;
} t_utils;


typedef struct s_utilsd
{
	int		i;
	int		j;
	char	*trimmed_command;
	char	*env_variable;
	char	*key;
	char	*tmp;
	char	*str1;
	char	*str2;
} t_d;


typedef struct s_cmd_to_execute {

	int index;
	int fd_in;
	int fd_out;
	int *previous_pipe;
	int *next_pipe;
	char *cmd;

} t_cmd_to_execute;


typedef struct s_parsed_args {

	char **redirections;
	char **cmd_args;

} t_parsed_args;

typedef struct s_pair_pipes
{
	int	pipe_fd1[2];
	int	pipe_fd2[2];
} t_pair_pipes;



void	rl_replace_line (const char *text, int clear_undo);


//MAIN.C
void	sig_init();
void	disable_ctrl_chars();
int		check_entry(char *line);
void	wait_for_input();
void	cpy_env(char **env);

//SIGNAL.C
void    signal_handler();

//PARSE_DOLLAR.C
void	parse_dollar(char **tab_cmds);
char	*find_env_variable (char *var_name);

//PARSE_REDIRECTION.C
void parse_redirection_right(char **tab_cmds);
void parse_redirection_left(char **tab_cmds);


//NORMALIZE_WITH_SPACE.C
void	cut_end_space(char **str);
void	normalize_with_space(char **str);
void	normalize_arguments_order(char **str1);

//LEXER.C
int		lexer(char *str);
char	**ft_split_lexer(char *str, char c);

//FT_LEXER_NO_QUOTE.C
char	**ft_split_lexer_no_quote(char *str);

//REDIRECTION.C
void	execute_command(char **parsed_args, int in_fd, int out_fd);
int 	process_delimiter(char *del);
int		process_redirection(char **redirections, int **in_out_fd);

//PROCESS_REDIRECTIONS.C

int process_double_right_r(char **redirection, int **in_out_fd);
int process_double_left_r(char **redirection, int **in_out_fd);
int process_single_right_r(char **redirection, int **in_out_fd);
int process_single_left_r(char **redirection, int **in_out_fd);

//UTILS.C
int		is_space(char c);
void	print_tab(char *title, char **tab);
int		size_tab(char **tab);
void	freemalloc(char **result, int j);
char	*ft_strndup(char *str, size_t n);
void	print_command_not_found(char *str);
int		is_chevron (char c);
void	free_struct(t_parsed_args **cmd_red_lst);
char	*concatenate_strings_with_spaces(char **strings);
void	remove_quote_in_tab(char **tab);
int key_already_exist(char *key);
char *get_key_from_token(char *token);
int		count_chr(char *str, char c);
int	is_quote(char c);
void	init_utils(t_utils *u);

// IS_BUILTINS.C
int		is_builtins(char *str);
int	execute_builtins(char **parsed_args);

// PRE_PARSING.C
int check_quotes(char *line);
int	check_blank_line(char *line);
int	check_entry(char *line);

// NORMALIZE_CMD.C
char	*normalize_cmd(char* str);

//CHECK_QUOTE.C
int	check_simple_quote(char *cmd, char *trimmed_command);
int	check_simple_quote2(char *cmd, char *trimmed_command);

//MS_PIPE.C
//void	execute_last_cmd(int pipe_fd[2], char **tab_cmds, int nbr_cmds);
//void	execute_first_cmd(int pipe_fd[2], char **tab_cmds);
//void	execute_first_cmd(t_cmd_to_execute cmd_to_execute);
//void	redirection (char *input_cmd, int previous_pipe[2], int next_pipe[2]);
//void	redirection (t_cmd_to_execute cmd_to_execute)
//void	execution (char *input_cmd);
//void	ms_pipe2(char **tab_cmds, int nbr_cmds);

//PROCESS_COMMANDS.C
int process_multiple_commands(t_parsed_args **cmd_red_lst);
int	process_single_command(t_parsed_args **cmd_red_lst, int *in_out_fd);




//BUILTINS
void	echo_process(char **cmd);
void	cd_process(char **current_command);
void	pwd_process();
int		unset_process(char **parsed_args);
void	env_process(char **parsed_args);
void	export_process(char **current_command);
void	add_to_env(char *ligne, char *value);
void    exit_process(char **parsed_args);
int		unset_process_str(char *key);

int ft_unset(char *token);
void	ft_export(char *token);
extern t_sig g_env;

#endif