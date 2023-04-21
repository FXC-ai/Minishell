/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:08:07 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 17:17:37 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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

static void	while_process(char *tab_cmds, t_utils *u, char **result)
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
