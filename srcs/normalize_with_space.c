/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_with_space.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:04:56 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/12 15:50:12 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/header.h"


void cut_end_space(char **str)
{
	int i;
	int length;
	char *copy_str;

	length = 0;
	i = 0;
	while ((*str)[length])
	{
		length++;
	}
	copy_str = malloc(length + 1);
	while ((*str)[i])
	{
		copy_str[i] = (*str)[i];
		i++;
	}
	copy_str[i] = '\0';
	length--;

	while (copy_str[length] == ' ')
	{
		length--;
	}
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

void normalize_with_space(char **str)
{
	char *p = *str;
	char *prev = NULL;
	char quote = '\0';

	while (*p != '\0')
	{
		if (quote != '\0' && *p == quote)
		{
			quote = '\0';
		}
		else if (quote == '\0' && (*p == '\'' || *p == '\"'))
		{
			quote = *p;
			p++;
		}
		else if (quote == '\0' && (*p == '<' || *p == '>'))
		{
			if (prev != NULL && !is_space(*prev) && *prev != '\'' && *prev != '\"' && *prev != *p) {
				ft_memmove(p + 1, p, ft_strlen(p) + 1);
				*p = ' ';
				prev = p;
			}
			p++;
			if (*(p) != '\0' && !is_space(*(p)) && *(p) != '\'' && *(p) != '\"' && *(p) != *(p - 1)) {
				ft_memmove(p + 1, p, ft_strlen(p) + 1);
				*p = ' ';
			}
		}
		else
		{
			prev = p;
			p++;
		}
	}
}

