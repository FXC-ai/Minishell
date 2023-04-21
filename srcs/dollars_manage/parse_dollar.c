/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:12 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/21 15:24:31 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

char	*find_env_variable(char *var_name)
{
	int	i;

	i = 0;
	while (g_env.env[i] != NULL)
	{
		if (ft_strncmp(g_env.env[i], var_name, ft_strlen(var_name)) == 0
			&& g_env.env[i][ft_strlen(var_name)] == '=')
			return (&g_env.env[i][ft_strlen(var_name) + 1]);
		i++;
	}
	return (NULL);
}

static void	part1(t_d *d, char **tab_cmds)
{
	d->tmp = ft_strndup(tab_cmds[d->i], ft_strlen(tab_cmds[d->i])
			- ft_strlen(d->trimmed_command));
	d->str1 = ft_strjoin(d->tmp, d->env_variable);
	d->str2 = ft_strndup(d->trimmed_command + d->j,
			ft_strlen(d->trimmed_command + d->j));
	free(tab_cmds[d->i]);
	tab_cmds[d->i] = NULL;
	tab_cmds[d->i] = ft_strjoin(d->str1, d->str2);
	free(d->key);
	free(d->tmp);
	free(d->str1);
	free(d->str2);
	d->trimmed_command = ft_strchr(tab_cmds[d->i], '$');
}

static void	part2(t_d *d, char **tab_cmds)
{
	if (d->trimmed_command[1] == '?')
		d->env_variable = ft_itoa(g_env.ms_errno);
	else
		d->env_variable = ft_strdup("");
	d->tmp = ft_strndup(tab_cmds[d->i], ft_strlen(tab_cmds[d->i])
			- ft_strlen(d->trimmed_command));
	d->str1 = ft_strjoin(d->tmp, d->env_variable);
	d->str2 = ft_strndup(d->trimmed_command + d->j,
			ft_strlen(d->trimmed_command + d->j));
	free(tab_cmds[d->i]);
	tab_cmds[d->i] = NULL;
	tab_cmds[d->i] = ft_strjoin(d->str1, d->str2);
	free(d->key);
	free(d->tmp);
	free(d->str1);
	free(d->str2);
	free(d->env_variable);
	d->trimmed_command = ft_strchr(tab_cmds[d->i], '$');
}

static void	process_dollar(t_d *d, char **tab_cmds)
{
	d->j = 1;
	while (is_space(d->trimmed_command[d->j]) != 1
		&& d->trimmed_command[d->j] != '\0'
		&& d->trimmed_command[d->j] != '\''
		&& d->trimmed_command[d->j] != '\"'
		&& d->trimmed_command[d->j] != '$')
		d->j++;
	if (check_simple_quote2(tab_cmds[d->i], d->trimmed_command) == 0)
	{
		d->key = ft_strndup(d->trimmed_command + 1, d->j - 1);
		d->env_variable = find_env_variable(d->key);
		if (d->env_variable != NULL)
		{
			part1(d, tab_cmds);
		}
		else
		{
			part2(d, tab_cmds);
		}
	}
	else
	{
		d->trimmed_command = ft_strchr(d->trimmed_command +1, '$');
	}	
}

void	parse_dollar(char **tab_cmds)
{
	t_d	d;

	d.i = 0;
	while (tab_cmds[d.i] != NULL)
	{
		d.trimmed_command = ft_strchr(tab_cmds[d.i], '$');
		if (d.trimmed_command != NULL && (!is_space(d.trimmed_command[1])
				&& d.trimmed_command[1] != '\0'))
		{
			while (d.trimmed_command != NULL && *d.trimmed_command != '\0')
			{
				process_dollar(&d, tab_cmds);
			}
		}
		d.i++;
	}
}
