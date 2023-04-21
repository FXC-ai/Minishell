/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:31:10 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 16:56:24 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	find_lenght(char *cmd, char chev_type)
{
	int	i;
	int	lenght;

	i = 0;
	lenght = 0;
	while (cmd[i])
	{
		if (cmd[i] == chev_type)
		{
			if (cmd[i + 1] == chev_type)
				i++;
			i++;
			while (is_space(cmd[i]) == 1)
				i++;
			while (cmd[i] && cmd[i] != ' ' && !is_chevron(cmd[i]))
				i++;
			lenght = i;
			break ;
		}
		i++;
	}
	return (lenght);
}

static int	find_lenght_command(char *cmd)
{
	t_utils	u;
	int		length;

	init_utils(&u);
	length = 0;
	while (cmd[u.i])
	{
		if (cmd[u.i] == '\'' || cmd[u.i] == '\"')
		{
			if (u.in_quote == 0)
			{
				u.quote = cmd[u.i];
				u.in_quote = 1;
			}
			else if (cmd[u.i] == u.quote)
				u.in_quote = 0;
		}
		if (cmd[u.i] && u.in_quote == 0 && is_chevron(cmd[u.i]))
			return (length);
		length++;
		u.i++;
	}
	return (length);
}

static	void while_process(char *tab_cmds, t_utils *u, char **result)
{
	if (tab_cmds[u->i] == '\'' || tab_cmds[u->i] == '\"')
	{
		if (u->in_quote == 0)
		{
			u->quote = tab_cmds[u->i];
			u->in_quote = 1;
		}
		else if (tab_cmds[u->i] == u->quote)
			u->in_quote = 0;
	}
	if (u->in_quote == 0 && (tab_cmds[u->i] == '<' || tab_cmds[u->i] == '>'))
	{
		u->count = find_lenght(tab_cmds + u->i, tab_cmds[u->i]);
		result[u->j++] = ft_substr(tab_cmds, u->i, u->count);
		u->i += u->count - 2;
	}
	u->i++;
}

char	**separate_redirections(char *tab_cmds)
{
	t_utils	u;
	char	**result;
	int		nbr_chev;

	init_utils(&u);
	nbr_chev = is_valid_chevron(tab_cmds, '>');
	nbr_chev += is_valid_chevron(tab_cmds, '<');
	result = malloc(sizeof(char *) * (nbr_chev + 1));
	if (result == NULL)
		return (NULL);
	while (tab_cmds[u.i])
	{
		while_process(tab_cmds, &u, result);
	}
	result[u.j] = NULL;
	return (result);
}

char	**separate_command(char *tab_cmds)
{
	int		i;
	int		j;
	int		length;
	char	**result;

	j = 0;
	i = 0;
	while (tab_cmds[i])
	{
		length = find_lenght_command(tab_cmds + i);
		if (length != 0)
			j++;
		i += length;
		while (is_chevron(tab_cmds[i]))
		{			
			while (tab_cmds[i] && is_chevron(tab_cmds[i]))
				i++;
			while (tab_cmds[i] && (is_space(tab_cmds[i])))
				i++;
			while (tab_cmds[i] && !is_space(tab_cmds[i])
				&& !is_chevron(tab_cmds[i]))
				i++;
			while (tab_cmds[i] && (is_space(tab_cmds[i])))
				i++;
		}
	}
	result = malloc((j + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tab_cmds[i])
	{
		length = find_lenght_command(tab_cmds + i);
		if (length != 0)
		{
			result[j] = ft_substr(tab_cmds, i, length);
			j++;
		}
		i += length;
		while (is_chevron(tab_cmds[i]))
		{			
			while (tab_cmds[i] && is_chevron(tab_cmds[i]))
				i++;
			while (tab_cmds[i] && (is_space(tab_cmds[i])))
				i++;
			while (tab_cmds[i] && !is_space(tab_cmds[i])
				&& !is_chevron(tab_cmds[i]))
				i++;
			while (tab_cmds[i] && (is_space(tab_cmds[i])))
				i++;
		}
	}
	result[j] = NULL;
	return (result);
}

t_parsed_args	**init_parsed_args(char **tab_cmds)
{
	t_parsed_args	**list_struct;
	t_parsed_args	*current_struct;
	char			**tmp;
	int				i;

	list_struct = malloc((size_tab(tab_cmds) + 1) * sizeof(t_parsed_args *));
	if (list_struct == NULL)
		return (NULL);
	i = 0;
	while (tab_cmds[i])
	{
		current_struct = malloc(sizeof(t_parsed_args));
		if (current_struct == NULL)
			return (NULL);
		tmp = separate_command(tab_cmds[i]);
		current_struct->cmd_args
			= ft_split_lexer_no_quote(concatenate_strings_with_spaces(tmp));
		remove_quote_in_tab(current_struct->cmd_args);
		freemalloc(tmp, size_tab(tmp));
		current_struct->redirections = separate_redirections(tab_cmds[i]);
		print_tab("redirections", current_struct->redirections);
		print_tab(" command ", current_struct->cmd_args);
		list_struct[i] = current_struct;
		i++;
	}
	list_struct[i] = NULL;
	return (list_struct);
}
