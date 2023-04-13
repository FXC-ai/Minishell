/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lexer_no_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:59:24 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/13 15:29:53 by vgiordan         ###   ########.fr       */
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
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}


static int process(char const *s, char **result, char c)
{
    int i = 0;
    int j = 0;
    int words_count;
    int word_start;
    int word_end;
    int start = 0;
    int in_quotes = 0;
    char quote_char = '\0';

    words_count = count_chr(s, c);
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
            word_start = start;
            word_end = i;

            // Check if the string begins and ends with the same quote character
            if ((s[word_start] == '\'' && s[word_end - 1] == '\'') || (s[word_start] == '\"' && s[word_end - 1] == '\"'))
            {
                word_start++;
                word_end--;
            }

            if (j < words_count)
            {
                result[j++] = word_dup(s, word_start, word_end);
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
    if (in_quotes == 1)
        return (-2);
    if (!in_quotes && j < words_count)
    {
        word_start = start;
        word_end = i;

        // Check if the string begins and ends with the same quote character
        if ((s[word_start] == '\'' && s[word_end - 1] == '\'') || (s[word_start] == '\"' && s[word_end - 1] == '\"'))
        {
            word_start++;
            word_end--;
        }

        result[j++] = word_dup(s, word_start, word_end);
        if (!result[j - 1])
        {
            freemalloc(result, j - 1);
            return (-1);
        }
    }
    result[j] = NULL;
    return (0);
}

char	**ft_split_lexer_no_quote(char const *s, char c)
{
	char	**result;
	int     r;

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
