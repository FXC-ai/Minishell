#include "includes/header.h"

static int  is_quote(char c)
{
    return (c == '\'' || c == '"');
}

static int count_words(char *str)
{
    int i = 0;
    int count = 0;
    int in_quotes = 0;
    int in_word = 0;
    char quote_char = '\0';
    while(str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        
        while (str[i] && is_quote(str[i]) == 0)
        {
            in_word = 1;
            i++;
            
        }
        quote_char = str[i];
        if(str[i])
        {
            in_quotes = 1;
            i++;
        }
            
        while (str[i] && str[i] != quote_char)
        {
            i++;
        }
        if(str[i])
            i++;
        count += (in_quotes + in_word);
        in_quotes = 0;
        in_word = 0; 
    }
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



static int process(char *str, char **result)
{
    int i = 0;
    int j = 0;
    int words_count;
    int start;
    char quote_char = '\0';
    char *check_result;

    words_count = count_words(str);
    printf("count %d\n", words_count);
    while(str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        start = i;
        while (str[i] && is_quote(str[i]) == 0)
        {
            i++;
        }
        if (start < i)
        {
            result[j++] = word_dup(str, start, i);
            check_result = result[j-1];
        }
        quote_char = str[i];
        if(str[i])
        {
            i++;
        }
        start = i;
        while (str[i] && str[i] != quote_char)
        {
            i++;
        }
        if (is_quote(str[start-1])==1)
        {
            result[j++] = word_dup(str, start-1, i+1);
            check_result = result[j-1];
        }
        if(str[i])
            i++;
    }
    result[j] = NULL;
    return (0);
}



char	**ft_split_lexer(char *s)
{
	char	**result;

	result = malloc((count_words(s) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (process(s, result) == -1)
		return (NULL);
	return (result);
}


char **lexer(char *str)
{
	char	**result;
	int		i;

	i = 0;
	result = ft_split_lexer(str);
	while (result[i])
	{
		printf("str %d = [%s]\n", i, result[i]);
		i++;
	}
	return (result);
}

static int size_tab(char **tab)
{
    int c =0;

    while (tab[c] != NULL)
    {
        c++;
    }
    return c;
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

int main(int argc, char const *argv[])
{
    char *str = "ls -la";
    char *str1 = "<<LIM cat -e";
    char *str2 = "<infile cat -e | wc > \"outfile\"";
    char *str3 = "echo \"'\"";
    char *str4 = "cd ../chemin/vers/fichier";
    char *str5 = "exit 2123";
    char *str6 = "/bin/ls 'abc";
    char *str7 = " 'cat file | grep bla | more";

    char **r;
    
    printf("\nTEST = [%s]\n", str);
    r = lexer(str);
    freemalloc(r , size_tab(r));
    

    
    
    printf("\nTEST = [%s]\n", str1);
    r = lexer(str1);
    freemalloc(r , size_tab(r));
    
    printf("\n TEST = [%s]\n", str2);
    r = lexer(str2);
    freemalloc(r , size_tab(r));

    printf("\n TEST = [%s]\n", str3);
    r = lexer(str3);
    freemalloc(r , size_tab(r));

    printf("\n TEST = [%s]\n", str4);
    r = lexer(str4);
    freemalloc(r , size_tab(r));

    printf("\n TEST = [%s]\n", str5);
    r = lexer(str5);
    freemalloc(r , size_tab(r));

    printf("\n TEST = [%s]\n", str6);
    r = lexer(str6);
    freemalloc(r , size_tab(r));

    printf("\n TEST = [%s]\n", str7);
    r = lexer(str7);
    freemalloc(r , size_tab(r));
    




    return 0;
}
