//#include "includes/header.h"
#include <stdio.h>
#include <stdlib.h>

static int  is_quote(char c)
{
    return (c == '\'' || c == '"');
}



static int count_chr(const char *str, char c)
{
    int count;
    int i;
    int in_quote;
    char quote;
    char check_c;


    count = 0;
    i = 0;
    in_quote = 0;
    quote = '\0';

    while (str[i] != '\0')
    {
        check_c = str[i];
        if (str[i] == c && in_quote == 0)
        {
            count++;
        }
        if (is_quote(str[i]) == 1 && in_quote == 0)
        {
            in_quote = 1;
            quote = str[i];
            i++;
        }
        if (str[i] == quote && in_quote == 1)
        {
            in_quote = 0;
            quote = '\0';
        }
        i++;
    }
    if (str[i-1] != c)
    {
        count++;
    }
    return count;
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

    words_count = count_chr(s, c);
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


char	**ft_split_lexer(char const *s, char c)
{
	char	**result;

	result = malloc((count_chr(s,c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (process(s, result, c) == -1)
		return (NULL);
	return (result);
}


int main ()
{

    
    char *str = "ls -la";
    char *str1 = "<<LIM cat -e";
    char *str2 = "<infile cat -e > \"outfile\" | wc -l";
    char *str3 = "echo \"'\"";
    char *str4 = "cd ../chemin/v'|'e''rs/fichi""er";
    char *str5 = "exit 2123";
    char *str6 = "/bin/ls 'abc";
    char *str7 = "111111 | 2222222 |   ls   -l'a'| 33333333 '|' 333333 \"|\" | 444444|     ";



	char	**result;
	int		i;

	i = 0;
	result = ft_split_lexer(str7, '|');
	while (result[i])
	{
		printf("str %d = [%s]\n", i, result[i]);
		i++;
	}
    /*
    printf("[%s] : %d\n", str1 ,count_pipe(str1));
    printf("[%s] : %d\n", str2 ,count_pipe(str2));
    printf("[%s] : %d\n", str3 ,count_pipe(str3));
    printf("[%s] : %d\n", str4 ,count_pipe(str4));
    printf("[%s] : %d\n", str5 ,count_pipe(str5));
    printf("[%s] : %d\n", str6 ,count_pipe(str6));
    printf("[%s] : %d\n", str7 ,count_pipe(str7));
    */


}