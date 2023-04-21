/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:35:07 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 15:29:17 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	malloc_error(void)
{
	perror("Erreur d'allocation de mémoire");
	exit(1);
}

char	*concatenate_strings_with_spaces(char **strings)
{
	int		i;
	char	*dest;
	int		total_length;
	char	*result;

	total_length = 0;
	i = 0;
	while (strings[i])
		total_length += ft_strlen(strings[i++]);
	total_length += i - 1 + 1;
	result = malloc(total_length * sizeof(char));
	if (result == NULL)
		malloc_error();
	dest = result;
	i = 0;
	while (strings[i])
	{
		if (i != 0)
			*dest++ = ' ';
		ft_strlcpy(dest, strings[i], ft_strlen(strings[i]) + 1);
		dest += ft_strlen(strings[i++]);
	}
	*dest = '\0';
	return (result);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v');
}

void	print_tab(char *title, char **tab)
{
	int	i;

	i = 0;
	printf("--------------%s------------\n", title);
	if (tab[i] == NULL)
	{
		printf("TAB IS NULL\n");
		return ;
	}
	while (tab[i])
	{
		printf("line [%d]: [%s]\n", i, tab[i]);
		i++;
	}
	printf("-----------------------------\n");
}

char	*ft_strndup(char *str, size_t n)
{
	char		*result;
	size_t		i;

	if (str == NULL)
		return (NULL);
	if (ft_strlen(str) <= n)
	{
		return (ft_strdup(str));
	}
	result = malloc(sizeof(char) * (n + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		result[i] = str[i];
		i++;
	}
	result[n] = '\0';
	return (result);
}
