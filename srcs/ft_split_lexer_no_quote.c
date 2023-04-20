/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer_no_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:59:24 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/20 11:34:35 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static int	count_chr_no_quote(const char *str)
{
	int		count;
	int		i;
	int		in_quote;
	char	quote;
	int		in_word;

	count = 0;
	i = 0;
	in_quote = 0;
	quote = '\0';
	in_word = 0;
	while (str[i] != '\0')
	{
		if (in_word == 0 && in_quote == 0 && !is_space(str[i]))
		{
			if (is_quote(str[i]))
			{
				quote = str[i];
				in_quote = 1;
			}
			in_word = 1;
			count++;
		}
		else if (in_word == 1 && in_quote == 0 && is_quote(str[i]))
		{
			quote = str[i];
			in_quote = 1;
		}
		else if (in_word == 1 && in_quote == 1 && str[i] == quote)
		{
			quote = '\0';
			in_quote = 0;
		}
		else if (in_word == 1 && in_quote == 0 && is_space(str[i]))
			in_word = 0;
		i++;
	}
	return (count);
}

static int	process_quotes(char const *str, int *i, int *in_quote, char *quote)
{
	if (is_quote(str[*i]))
	{
		if (*in_quote)
		{
			if (str[*i] == *quote)
			{
				*quote = '\0';
				*in_quote = 0;
			}
		}
		else
		{
			*quote = str[*i];
			*in_quote = 1;
		}
		return (1);
	}
	return (0);
}

static int	process_words(char *str, int *i, int *in_word, int *start, int in_quote)
{
	if (!is_space(str[*i]) && !in_quote)
	{
		if (!*in_word)
		{
			*start = *i;
			*in_word = 1;
		}
		return (1);
	}
	return (0);
}

static int	process_spaces(char *str, int *i, int *in_word, int *j, int *start, int in_quote, char **result)
{
	if (is_space(str[*i]) && !in_quote)
	{
		if (*in_word)
		{
			*in_word = 0;
			result[(*j)++] = ft_substr(str, *start, *i - *start);
		}
		return (1);
	}
	return (0);
}

int	process(char *str, char **result, int nb_word)
{
	int		i;
	int		j;
	int		start;
	int		in_quote;
	char	quote;
	int		in_word;

	i = 0;
	j = 0;
	start = 0;
	in_quote = 0;
	quote = '\0';
	in_word = 0;
	while (str[i] != '\0')
	{
		if (!process_quotes(str, &i, &in_quote, &quote))
			if (!process_words(str, &i, &in_word, &start, in_quote))
				process_spaces(str, &i, &in_word, &j, &start, in_quote, result);
		i++;
	}
	if (j < nb_word)
		result[j++] = ft_substr(str, start, i - start);
	result[j] = NULL;
	return (0);
}

char	**ft_split_lexer_no_quote(char *s)
{
	char	**result;
	int		r;
	int		nb_word;

	nb_word = count_chr_no_quote(s);
	result = malloc((nb_word + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	r = process(s, result, nb_word);
	if (r == -1)
		return (NULL);
	if (r == -2)
	{
		printf("Please close \" or \'\n");
		return (NULL);
	}
	free(s);
	return (result);
}
