/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:31:10 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 17:17:21 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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

static void	part1(char *tab_cmds, t_utils *u)
{
	u->count = find_lenght_command(tab_cmds + u->i);
	if (u->count != 0)
		u->j++;
	u->i += u->count;
	while (is_chevron(tab_cmds[u->i]))
	{			
		while (tab_cmds[u->i] && is_chevron(tab_cmds[u->i]))
			u->i++;
		while (tab_cmds[u->i] && (is_space(tab_cmds[u->i])))
			u->i++;
		while (tab_cmds[u->i] && !is_space(tab_cmds[u->i])
			&& !is_chevron(tab_cmds[u->i]))
			u->i++;
		while (tab_cmds[u->i] && (is_space(tab_cmds[u->i])))
			u->i++;
	}
}

static void	part2(char *tab_cmds, t_utils *u, char **result)
{
	u->count = find_lenght_command(tab_cmds + u->i);
	if (u->count != 0)
	{
		result[u->j] = ft_substr(tab_cmds, u->i, u->count);
		u->j++;
	}
	u->i += u->count;
	while (is_chevron(tab_cmds[u->i]))
	{			
		while (tab_cmds[u->i] && is_chevron(tab_cmds[u->i]))
			u->i++;
		while (tab_cmds[u->i] && (is_space(tab_cmds[u->i])))
			u->i++;
		while (tab_cmds[u->i] && !is_space(tab_cmds[u->i])
			&& !is_chevron(tab_cmds[u->i]))
			u->i++;
		while (tab_cmds[u->i] && (is_space(tab_cmds[u->i])))
			u->i++;
	}
}

char	**separate_command(char *tab_cmds)
{
	t_utils	u;
	char	**result;

	init_utils(&u);
	while (tab_cmds[u.i])
	{
		part1(tab_cmds, &u);
	}
	result = malloc((u.j + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	u.i = 0;
	u.j = 0;
	while (tab_cmds[u.i])
	{
		part2(tab_cmds, &u, result);
	}
	result[u.j] = NULL;
	return (result);
}
