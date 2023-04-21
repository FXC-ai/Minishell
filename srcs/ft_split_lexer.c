#include "../includes/header.h"

static char	*word_dup(char *str, int start, int finish)
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

static int process(char *s, char **result, char c)
{
	int i = 0;
	int j = 0;
	int words_count;
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
	if (in_quotes == 1)
		return (-2);
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

char	**ft_split_lexer(char *s, char c)
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
