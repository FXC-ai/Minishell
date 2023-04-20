/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_with_space.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:04:56 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/20 21:53:44 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	cut_end_space(char **str)
{
	int		i;
	int		length;
	char	*copy_str;

	length = 0;
	i = 0;
	while ((*str)[length])
		length++;
	copy_str = malloc(length + 1);
	while ((*str)[i])
	{
		copy_str[i] = (*str)[i];
		i++;
	}
	copy_str[i] = '\0';
	length--;
	while (copy_str[length] == ' ')
		length--;
	free(*str);
	*str = malloc(length + 2);
	i = 0;
	while (i <= length)
	{
		(*str)[i] = copy_str[i];
		i++;
	}
	(*str)[i] = '\0';
	free(copy_str);
}
