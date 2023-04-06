/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:35:07 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/06 11:37:40 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

void	print_tab(char **tab)
{
	int i;

	i = 0;
	printf("--------------TAB------------\n");
	while (tab[i])
	{
		printf("line : [%s]\n",tab[i++]);
	}
	printf("-----------------------------\n");
}

int	get_max_length(char *str1, char *str2)
{
	int	a;
	int	b;

	a = ft_strlen(str1);
	b = ft_strlen(str2);
	if (a >= b)
		return (a);
	else
		return (b);
}

int	is_builtins(char *str)
{
	
	if (ft_strncmp(str, "echo", get_max_length(str, "echo")) == 0)
		return (1);
	if (ft_strncmp(str, "cd", get_max_length(str, "cd")) == 0)
		return (2);
	if (ft_strncmp(str, "pwd", get_max_length(str, "pwd")) == 0)
		return (3);
	if (ft_strncmp(str, "export", get_max_length(str, "export")) == 0)
		return (4);
	if (ft_strncmp(str, "unset", get_max_length(str, "unset")) == 0)
		return (5);
	if (ft_strncmp(str, "env", get_max_length(str, "env")) == 0)
		return (6);
	if (ft_strncmp(str, "exit", get_max_length(str, "exit")) == 0)
		return (7);
	return (0);
}

void	ft_free_tabs(char **tab, int h)
{
	int	i;

	i = 0;
	while (i <= h)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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

int	size_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != NULL)
		count++;
	return (count);
}



