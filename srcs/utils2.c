/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:51:25 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/20 16:58:36 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	free_struct(t_parsed_args **cmd_red_lst)
{
	int	i;

	i = 0;
	while (cmd_red_lst[i])
	{
		freemalloc(cmd_red_lst[i]->cmd_args,
			size_tab(cmd_red_lst[i]->cmd_args));
		freemalloc(cmd_red_lst[i]->redirections,
			size_tab(cmd_red_lst[i]->redirections));
		free(cmd_red_lst[i]);
		i++;
	}	
	free(cmd_red_lst);
}

char	*get_key_from_token(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '=')
		{
			return (ft_substr(token, 0, i));
		}
		i++;
	}
	return (token);
}

int	key_already_exist(char *key)
{
	int	i;
	int	j;

	i = 0;
	while (global_sig.env[i])
	{
		j = 0;
		while ((global_sig.env[i][j]) == key[j])
		{
			j++;
		}
		if (j == (int)ft_strlen(key))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	size_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != NULL)
		count++;
	return (count);
}

void	freemalloc(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		result[j] = NULL;
		j--;
	}
	free(result);
}
