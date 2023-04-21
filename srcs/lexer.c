/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:00:40 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 16:31:42 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	is_valid_chevron(char *tab_cmd, char chev_type)
{
	int		i;
	int		count;
	int		in_quote;
	char	quote;

	count = 0;
	i = 0;
	in_quote = 0;
	quote = '\0';
	while (tab_cmd[i] != '\0')
	{
		if (tab_cmd[i] == '\'' || tab_cmd[i] == '\"')
		{
			if (in_quote == 0)
			{
				quote = tab_cmd[i];
				in_quote = 1;
			}
			else if (tab_cmd[i] == quote)
			{
				quote = '\0';
				in_quote = 0;
			}
		}
		if (tab_cmd[i] == chev_type && in_quote == 0)
		{
			if (tab_cmd[i + 1] == chev_type)
				i++;
			i++;
			while (is_space(tab_cmd[i]) == 1)
				i++;
			if (is_chevron(tab_cmd[i]) == 1)
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}



int chr_is_in_quote (char *str, int ind_char)
{
	int		i;
	int		in_quote;
	char	quote;

	if ((size_t) ind_char > ft_strlen(str))
	{
		return (-1);
	}

	in_quote = 0;
	quote = '\0';
	i = 0;

	while (i < ind_char)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote == 0)
			{
				quote = str[i];
				in_quote = 1;
			}
			else if (str[i] == quote)
			{
				quote = '\0';
				in_quote = 0;
			}
		}
		i++;
	}
	return in_quote;

}

char	check_redirections (char *str, char type_chev)
{
	int	i;

	i = 1;
	if (str[i] == type_chev)
		i++;

	while (is_space(str[i]) && str[i] != '\0')
	{
		i++;
	}

	if (is_chevron(str[i]))
		return str[i];

	if (str[i] == '\0')
		return str[i];

	return (1);
}

int	check_redirections_process(char **tab_cmds)
{
	int		i;
	int		j;
	char	chk_char;

	i = 0;
	while (tab_cmds[i] != NULL)
	{
		j = 0;
		while (tab_cmds[i][j] != '\0')
		{
			if (is_chevron(tab_cmds[i][j]) && chr_is_in_quote(tab_cmds[i], j) == 0)
			{
				chk_char = check_redirections(tab_cmds[i] + j, tab_cmds[i][j]);
				if (chk_char != 1)
				{
					g_env.ms_errno = 258;
					ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
					if (is_chevron(chk_char))
					{
						ft_putchar_fd(chk_char ,2);
						ft_putstr_fd("'\n" ,2);
					}
					else
					{
						ft_putstr_fd("newline'\n" ,2);
					}
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int lexer(char *str)
{
	char			**result;
	char			c = '|';
	int				i;
	int				*in_out_fd;
	t_parsed_args	**cmd_red_lst;

	in_out_fd = malloc(2 * sizeof(int));
	if (in_out_fd == NULL)
		return (0);
	i = 0;
	printf("STRING %s\n", str);
	result = ft_split_lexer(str, c);
	print_tab("result", result);
	//print_tab("result qm", result);
	if (check_redirections_process(result) == 0)
	{
		free(in_out_fd);
		freemalloc(result, size_tab(result));
		return (1);
	}
	if (result == NULL)
		return (0);
	print_tab("result", result);
	parse_dollar(result);
	print_tab("result", result);
	cmd_red_lst = init_parsed_args(result);
	freemalloc(result, size_tab(result));
	in_out_fd[0] = STDIN_FILENO;
	in_out_fd[1] = STDOUT_FILENO;
	if (cmd_red_lst[1] == NULL)
	{
		if (process_single_command(cmd_red_lst, in_out_fd) == -1)
			return (-1);
	}
	else
	{
		if (process_multiple_commands(cmd_red_lst) == -1)
			return (-1);
	}
	free(in_out_fd);
	free_struct(cmd_red_lst);
	return (1);
}
