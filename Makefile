SRCS	=	$(addprefix srcs/, main.c signal.c is_builtins.c normalize_cmd.c lexer.c ft_split_lexer.c process_commands.c process_redirections.c \
				process_single_command.c process_commands2.c redirection.c ft_split_lexer_no_quote.c pre_parsing.c) \
			$(addprefix srcs/builtins/, echo.c cd.c pwd.c env.c exit.c unset.c export.c) \
			$(addprefix srcs/dollars_manage/, check_quote.c parse_dollar.c) \
			$(addprefix srcs/init_struct/, init_commands.c init_redirections.c init.c) \
			$(addprefix srcs/utils/, utils.c utils2.c utils3.c utils4.c utils5.c)



OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra

CC		= gcc

RM		= rm -f

NAME 	= minishell

INCLUDE = includes

#$@ = all, $< = server / client

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	make -C libft
	$(CC) -o $(NAME) $(OBJS) -Llibft -lft -I $(INCLUDE) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	${RM}  $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re