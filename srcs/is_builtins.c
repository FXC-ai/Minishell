/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:46:13 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/06 11:47:16 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	get_max_length(char *str1, char *str2)
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