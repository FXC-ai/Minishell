/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:58:03 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 18:46:39 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int count_words(char const *str, char c)
{
    int i = 0;
    int count = 0;
    int in_quotes = 0;
    char quote_char = '\0';

    while (str[i])
    {
        if ((str[i] == '\'' || str[i] == '\"') && (in_quotes == 0 || str[i] == quote_char))
        {
            in_quotes = !in_quotes;
            quote_char = str[i];
        }
        else if (str[i] == c && in_quotes == 0)
        {
            count++;
        }
        i++;
    }
    if (str[i - 1] != c)
        count++;
    return (count);
}


static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	freemalloc(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		result[j] = NULL;
		j--;
	}
	free(result);
}

/*static void parse(char const *s, char c, int *i, int *start)
{
    while (s[*i])
	{
		while (s[*i] == c && s[*i])
			i++;
		*start = *i;
		while (s[*i] != c && s[*i])
			i++;
		
	}
}*/


static int process(char const *s, char **result, char c)
{
    int i = 0;
    int j = 0;
    int words_count;
    int start = 0;
    int in_quotes = 0;
    char quote_char = '\0';

    words_count = count_words(s, c);
    printf("count %d\n", words_count);
    while (s[i])
    {
        
        
        if ((s[i] == '\'' || s[i] == '\"') && !in_quotes)
        {
            in_quotes = 1;
            quote_char = s[i];
        }
        else if ((s[i] == '\'' || s[i] == '\"') && in_quotes && s[i] == quote_char)
        {
            in_quotes = 0;
        }
        else if (!in_quotes && s[i] == c)
        {
            if (j < words_count)
            {
                result[j++] = word_dup(s, start, i);
                if (!result[j - 1])
                {
                    freemalloc(result, j - 1);
                    return (-1);
                }
            }
            while (s[i + 1] && s[i + 1] == ' ' && !in_quotes)
                i++;
            start = i + 1;
        }
        i++;
    }
    if (!in_quotes && j < words_count)
    {
        result[j++] = word_dup(s, start, i);
        if (!result[j - 1])
        {
            freemalloc(result, j - 1);
            return (-1);
        }
    }
    result[j] = NULL;
    return (0);
}



char	**ft_split_lexer(char const *s)
{
	char	**result;
    char    c;

    c = ' ';
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (process(s, result, c) == -1)
		return (NULL);
	return (result);
}

