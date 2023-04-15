/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:35:07 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/15 22:44:35 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

void	print_tab(char *title, char **tab)
{
	int i;

	i = 0;
	
	printf("--------------%s------------\n", title);
	if (tab[i] == NULL)
	{
		printf("TAB IS NULL\n");
		return ;
	}
	while (tab[i])
	{
		printf("line : [%s]\n",tab[i++]);
	}
	printf("-----------------------------\n");
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

void freemalloc(char **result, int j)
{
    while (j >= 0)
    {
        printf("Freeing result[%d] at address %p\n", j, (void *)result[j]);
        free(result[j]);
        result[j] = NULL;
        j--;
    }
    printf("Freeing result at address %p\n", (void *)result);
    free(result);
}



void	free_struct(t_parsed_args **cmd_red_lst)
{

	//char **parsed_args;
	int i;

	i = 0;
	while (cmd_red_lst[i])
	{
		print_tab("cmd_args",cmd_red_lst[i]->cmd_args);
		print_tab("redirection",cmd_red_lst[i]->redirections);

		freemalloc(cmd_red_lst[i]->cmd_args, size_tab(cmd_red_lst[i]->cmd_args));
		freemalloc(cmd_red_lst[i]->redirections, size_tab(cmd_red_lst[i]->redirections));
		free(cmd_red_lst[i]);
		i++;
	}
	
	free(cmd_red_lst);
}

int	size_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != NULL)
		count++;
	return (count);
}

char *ft_strndup(char *str, size_t n)
{
    char    	*result;
    size_t     i;

    if (str == NULL)
        return NULL;
   
    if (ft_strlen(str) <= n)
    {
        return ft_strdup(str);
    }
    
    result = malloc(sizeof(char) * (n + 1));
    if (result == NULL)
        return NULL;

    i = 0;
    while(i < n)
    {
        result[i] = str[i];
        i++;
    }
    result[n] = '\0';

    return result;
}

void	print_command_not_found(char *str)
{
	write(2, str, ft_strlen(str));
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int is_chevron (char c)
{
    return c == '>' || c == '<';
}
