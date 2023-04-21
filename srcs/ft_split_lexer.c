/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:58:03 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 12:58:23 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		exit(errno);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static int	handle_q(char *s, int *i, int *in_quotes, char *q_c)
{
	if ((s[*i] == '\'' || s[*i] == '\"') && !(*in_quotes))
	{
		*in_quotes = 1;
		*q_c = s[*i];
		return (1);
	}
	else if ((s[*i] == '\'' || s[*i] == '\"') && *in_quotes && s[*i] == *q_c)
	{
		*in_quotes = 0;
		return (1);
	}
	return (0);
}

static void	init_var(int *i, int *j, int *start, int *in_quotes)
{
	*i = -1;
	*j = 0;
	*start = 0;
	*in_quotes = 0;
}

static int	process(char *s, char **result, char c)
{
	int		i;
	int		j;
	int		start;
	int		in_quotes;
	char	q_c;

	init_var(&i, &j, &start, &in_quotes);
	q_c = '\0';
	while (s[i++])
	{
		if (handle_q(s, &i, &in_quotes, &q_c) == 0 && !in_quotes && s[i] == c)
		{
			if (j < count_chr(s, c))
				result[j++] = word_dup(s, start, i);
			while (s[i + 1] && s[i + 1] == ' ' && !in_quotes)
				i++;
			start = i + 1;
		}
	}
	if (in_quotes == 1)
		return (-2);
	if (!in_quotes && j < count_chr(s, c))
		result[j++] = word_dup(s, start, i);
	result[j] = NULL;
	return (0);
}

char	**ft_split_lexer(char *s, char c)
{
	char	**result;
	int		r;

	result = malloc((count_chr(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	r = process(s, result, c);
	if (r == -1)
		return (NULL);
	if (r == -2)
	{
		printf("Please close \" or \'\n");
		return (NULL);
	}
	return (result);
}
